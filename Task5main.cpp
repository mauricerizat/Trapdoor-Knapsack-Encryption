/*
TRAPDOOR KNAPSACK ENCRYPTION PROGRAM
*/

#include "header.h"

int main()
{
	cout << "Welcome to Trapdoor Knapsack Encryption Program" << endl;
	cout << "-------------------------------------------------------\n" << endl;
	
	cout << "Keys nust first be generated. Please input the required values..." << endl;
	
	int size;
	vector<uint64_t> a;
	vector<uint64_t> b;
	uint64_t m, w;
	char choice;
	
	getInput(size, a, m, w);
		
	cout << "\nSuper Increasing Knapsack: (";
	for(int i = 0; i < a.size(); ++i)
	{
		cout << a[i];
	
		(i+1 != a.size()) ? cout << ", " : cout << ") " << endl;
	}
	
	cout << "\n-------------------------------------------------------\n" << endl;
	
	generatePublicKey(a, b, w, m);
	
	cout << "Keys Generated!" << endl;
	
	//Displaying Public Key
	cout << "\nPublic Key: (";
	for(int i = 0; i < b.size(); ++i)
	{
		cout << b[i];
	
		(i+1 != b.size()) ? cout << ", " : cout << ") " << endl;
	}	
	
	cout << "\n-------------------------------------------------------\n" << endl;
	
	do
	{
		cout << "Select action:\n\t1. Encrypt\n\t2. Decrypt\n\t3. Exit" << endl;
		cout << "\nYour choice: ";
		cin >> choice;
		
		cin.clear();
		cin.ignore(10000, '\n');
		
		switch(choice)
		{
			case '1': {//Encryption
					cout << "\n-------------------------------------------------------\n" << endl;
					vector<uint64_t> ciphertext;
					encrypt(b, ciphertext);
					
					//Display Ciphertext
					cout << "\nCiphertext: (";
					for(int i = 0; i < ciphertext.size(); ++i)
					{
						cout << ciphertext[i];
					
						(i+1 != ciphertext.size()) ? cout << ", " : cout << ") " << endl;
					}
					cout << "\n-------------------------------------------------------\n" << endl;
				}
				break;
			case '2': {//Decryption
					cout << "\n-------------------------------------------------------\n" << endl;
											
					string plaintext = decrypt(a, m, w); 
		
					cout << "\nPlaintext: " << plaintext << endl;
					cout << "\n-------------------------------------------------------\n" << endl;
				}
				break;
			case '3': break;
			default: cout << "\nWrong option. Please try again" << endl;
				cout << "\n-------------------------------------------------------\n" << endl;
			
		}		
	}while(choice != '3');
	
	cout << "\n-------------------------------------------------------" << endl;
	cout << "Thank you for using the program" << endl;
	cout << "-------------------------------------------------------" << endl;
	
}
