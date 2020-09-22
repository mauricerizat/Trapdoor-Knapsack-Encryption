/*
TRAPDOOR KNAPSACK ENCRYPTION PROGRAM
*/

#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

bool isInteger(string);
uint64_t gcd(uint64_t, uint64_t);
void getInput(int&, vector<uint64_t>&, uint64_t&, uint64_t&);
void generatePublicKey(const vector<uint64_t>, vector<uint64_t>&, const uint64_t, const uint64_t);
uint64_t modular_mul(uint64_t, uint64_t, uint64_t);
void encrypt(const vector<uint64_t>, vector<uint64_t>&);
uint64_t aInverseModb(uint64_t, uint64_t);
string decrypt(const vector<uint64_t>, uint64_t, uint64_t);
string reverseString(string);
void getCiphertext (vector<uint64_t>&);

