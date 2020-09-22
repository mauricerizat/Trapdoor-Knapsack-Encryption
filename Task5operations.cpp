/*
TRAPDOOR KNAPSACK ENCRYPTION PROGRAM
*/

#include "header.h"

void getCiphertext (vector<uint64_t>& ciphertext)
{
	uint64_t ci;
	string input;
		
	cout << "\nEnter value of each ciphertext element seperated by space. " << endl;
	cout << "Enter \")\" to denote end of ciphertext." << endl;
	cout << "\nYour Input: ";
	
	while(true)
	{
		cin >> input;
		
		if (input[0] == ')')
			break;
		
		if (!isInteger(input))
		{
			cout << "\nPlease input only Integers." << endl;
			cout << "Please continue.\n" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		
		ci = stoull(input);
		
		ciphertext.push_back(ci);
	}
	
	cin.clear();
	cin.ignore(10000, '\n');	
}

string decrypt(const vector<uint64_t> a, uint64_t m, uint64_t w)
{
	cout << "\nDecryption" << endl;
	
	vector<uint64_t> ciphertext;
	
	getCiphertext(ciphertext);
						
	cout << "\nReceived ciphertext: (";
	for(int i = 0; i < ciphertext.size(); ++i)
	{
		cout << ciphertext[i];
	
		(i+1 != ciphertext.size()) ? cout << ", " : cout << ") " << endl;
	}
	
	string plainStream = "";
	
	uint64_t wInv = aInverseModb(w, m);
	
	for (int i = 0; i < ciphertext.size(); ++i)
	{
		uint64_t R = modular_mul(ciphertext[i], wInv, m);
		
		//cout << R << endl;
		
		string currStream = "";
		
		for (int j = a.size()-1; j >= 0; --j)
		{	
			if (R >= a[j])
			{
				currStream = currStream + "1";
				R -= a[j];
			}
			else
				currStream = currStream + "0";
		}
		
		currStream = reverseString(currStream);
		
		//cout << plainStream << " : " << currStream << endl;
		
		try
		{
			if (i+1 == ciphertext.size())
			{
				int needed = 8 * ((plainStream.length() / 8) + 1);
				
				currStream = currStream.substr((currStream.length()-(needed-plainStream.length())));
			}
		}
		catch (exception& e)
		{
		}
		
		
		plainStream = plainStream + currStream;
	}
	
	//cout << plainStream << endl;
	
	//converting bits to characters
	string plaintext = "";
	
	int iter = plainStream.length()/8;
	
	for (int i = 0; i < iter; ++i)
	{		
		string currStream = plainStream.substr(0, 8);
		
		plainStream = plainStream.substr(8);
		
		plaintext = plaintext + (char)stoi(currStream, 0, 2);
	}
	
	return plaintext;
}

void encrypt(const vector<uint64_t> b, vector<uint64_t>& ciphertext)
{
	cout << "Encryption" << endl;
	
	string message;
	
	cout << "\nEnter message to encrypt: ";
	cin >> message;
	
	cin.clear();
	cin.ignore(10000, '\n');
	
	string bitStream = "";
	
	//Creating bitStream
	for (int i = 0; i < message.length(); ++i)
	{
		string charBits = bitset<8>(message[i]).to_string();
		
		bitStream = bitStream + charBits;	
	}
	
	//cout << bitStream << endl;
	
	int iter = bitStream.length()/b.size();
	
	for(int i = 0; i < iter; ++ i)
	{
		string currSet = bitStream.substr(0, b.size());

		//cout << currSet << endl;
		
		bitStream = bitStream.substr(b.size());
		
		uint64_t T = 0;
		
		for (int j = 0; j < b.size(); ++j) 	
		{
			if (currSet[j] == '1')
				T += b[j];
		}
		
		ciphertext.push_back(T);
	}	
		
	if (bitStream.length() != 0)
	{
		while  (bitStream.length() < b.size())
		{
			bitStream = "0" + bitStream;
		}	
		
		uint64_t T = 0;
		
		for (int i = 0; i < b.size(); ++i)
		{
			if (bitStream[i] == '1')
				T += b[i];
		}
		
		ciphertext.push_back(T);
	}
	
}

void generatePublicKey(const vector<uint64_t> a, vector<uint64_t>& b, const uint64_t w, const uint64_t m)
{
	for (int i = 0; i < a.size(); ++i)
	{
		uint64_t bi = modular_mul(a[i], w, m);
		
		b.push_back(bi); 
	}	
}

void getInput(int& size, vector<uint64_t>& a, uint64_t& m, uint64_t& w)
{
	string input;
	uint64_t sum = 0;
	
	bool moveOn = false;
	
	//Accepting size of knapsack from user
	
	do
	{
		cout << "\nEnter size of super-increasing knapsack: ";
		cin >> input;
		
		if (!isInteger(input))
			cout << "Please enter only an Integer in this field. Please try again." << endl;
		else
		{
			size = stoi(input);
			moveOn = true;
		}
		
		cin.clear();
		cin.ignore(10000, '\n');	
		
	}while(moveOn == false);
	
	moveOn = false;
	
	//Accepting super-increasing knapsack from user
	uint64_t ai;
		
	cout << "\nEnter value of each knapsack element seperated by space: ";
	
	for (int i = 0; i < size; ++i)
	{
		cin >> input;
		
		if (!isInteger(input))
		{
			--i;
			cout << "\nPlease input only Integers in correct order." << endl;
			cout << "Please try again, continuing from element " << i+2 << " of " << size << ".\n " << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		
		ai = stoull(input);
		
		if (ai <= sum)
		{	
			--i;
			cout << "\nError!" << endl; 
			cout << "Value of entered element must exceed than sum of all preceeding elements." << endl;
			cout << "Please try again, continuing from element " << i+2 << " of " << size << ".\n" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;		
		}
		
		a.push_back(ai);
		sum += ai;
	}	
	
	cin.clear();
	cin.ignore(10000, '\n');	
		
	//Accepting m from user
	do
	{
		cout << "\nEnter value of modulus: ";
		cin >> input;
		
		if (!isInteger(input))
		{
			cout << "\nPlease enter only an Integer in this field. Please try again." << endl;
			continue;
		}
		
		m = stoull(input);
		
		if (m <= sum)
		{
			cout << "\nValue of modulus must exceed sum of all knapsack elements." << endl;
			cout << "Please try again." << endl;
		}
		else
			moveOn = true;
		
		cin.clear();
		cin.ignore(10000, '\n');

	}while(moveOn == false);
	
	moveOn = false;
	
	//Accepting w from user
	do
	{
		cout << "\nEnter value of multiplier: ";
		cin >> input;
		
		if (!isInteger(input))
		{
			cout << "\nPlease enter only an Integer in this field. Please try again." << endl;
			continue;
		}
		
		w = stoull(input);
		
		if (gcd(w, m) != 1)
		{
			cout << "\nValue of multiplier must be relatively prime to value of modulus." << endl;
			cout << "Please try again." << endl;
		}
		else
			moveOn = true;
		
		cin.clear();
		cin.ignore(10000, '\n');
		
	}while(moveOn == false);

	moveOn = false;
}

//Check if given string contains only Integers
bool isInteger(string num)
{
	for (int i = 0; i < num.length(); ++i)
	{
		if (num[i] < '0' || num[i] > '9')
			return false;
	}
	
	return true;
}

//Calculate gcd or two values using Euclidean Algorithm
uint64_t gcd(uint64_t a, uint64_t b)
{
	if (a == 0 || b == 0)
		return 0;
	
	if (a < b)
	{
		uint64_t t = a;
		a = b;
		b = t;
	}
	
	uint64_t rem = a%b;
	
	while (rem > 0)
	{
		a = b;
		b = rem;
		rem = a % b;
	}

	return b;
	
}

//Perform modular multiplication
uint64_t modular_mul(uint64_t a, uint64_t b, uint64_t mod) 
{
	uint64_t result = 0;
	
	for (uint64_t current_term = a; b; b >>= 1) 
	{
		if (b & 1) 
		{
			result = (result + current_term) % mod;
		}
		
		current_term = 2 * current_term % mod;
	}
	return result;
}

uint64_t aInverseModb(uint64_t a, uint64_t b)
{
	uint64_t n1 = b;
	uint64_t n2 = a;
	
	long long int a1 = 1;
	long long int b1 = 0;
	long long int a2 = 0;
	long long int b2 = 1;
	
	long long int q = n1 / n2;
	long long int r = n1 % n2;
	
	while (r > 0)
	{
		n1 = n2;
		n2 = r;
		
		long long int t = a2;
		a2 = a1 - q*a2;
		a1 = t;
		
		t = b2;
		b2 = b1 - q*b2;
		b1 = t;
		
		q = n1 / n2;
		r = n1 % n2;	
	}
	
	if (b2 < 0)
		b2 = b + b2;
	
	return b2;
}

string reverseString(string str)
{
	string rev = "";
	
	for (int i = str.length()-1; i >= 0; --i)
	{
		rev = rev + str[i];		
	}
	
	return rev;
}






