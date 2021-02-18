//************************************************************** 
// Project: Simplified DES Algorithm
// Name: Thomas Bauer 
// CMPS 4663 - Network Security
// Date: 04/25/2019 
// File: SimplifiedDES.cpp
//*************************************************************** 

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string permutation(string, string, int);
int circLeftShift(unsigned int, unsigned int);

int main() {
	int k = 0;					//key
	int num = 0;				//number for switch statement
	int lhs;					//left hand side of binary number
	int rhs;					//right hand side of binary number
	int xor;					//result from xor operation
	int ipLeft;					//left half of initial permutation
	int ipRight;				//right half of initial permutation
	int newPermLeft;			//left half of new permutation
	int newPermRight;			//right half of new permutation
	int decimal;
	int permTemp;				//temp variable for permutation calculations
	int zero = 0;
	int initPerm = 1;			//initial permutation
	bool good = false;			//boolean variable for input checks
	string lhsRow;				//left hand side of the row
	string lhsColumn;			//left hands side of the column
	string rhsRow;				//right hand side of the row
	string rhsColumn;			//right hand side of the column
	string binconv;
	string plaintxt;			//plaintext inputted by user
	string p10;					//10-bit permutation
	string perm10;				//alternate 10-bit permutation variable
	string perm8;				//8-bit permutation
	string perm4;				//4-bit permutation
	string k1;					//key #1
	string k2;					//key #2
	string newPerm;				//new permutation variable
	string ipPerm;				//initial permutation variable
	string invIP;				//inverse of initial permutation
	string expPerm;				//expansion / permutation variable
	string s0box;				//S-box S0
	string s1box;				//S-box S1
	string sResult;				//result from concatenation of sbox variables

	while (!good) {
		cout << "Please enter a number between 0 and 1024: ";
		cin >> k;
		//check for correct input type
		if (!cin) {
			cout << "Please only enter numbers in the given range." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		} 
		else{
			//check for correct range of key value
			if (k >= 0 && k < 1024) {
				good = true;
			}
			else {
				good = false;
				cout << "\nThe number you entered will not work, please try another.\n";
			}
		}
	}
	cin.ignore();
	good = false;

	while (!good) {
		cout << "\nPlease enter a word or short phrase" << endl;
		cout << "(letters must all be capitalized and numbers can be from 0 - 9) : \n";
		getline(cin, plaintxt);

		for (int i = 0; i < plaintxt.length(); i++) {
			//check for input variables matching either all capital letters or the 
			//integers 0-9
			if((plaintxt[i] >= 65 && plaintxt[i] <= 90) || (plaintxt[i] >= 48 && plaintxt[i] <= 57) || plaintxt[i] == 32){			
				if (plaintxt[i] == 32)
					plaintxt.erase(i, 1);
				good = true;
			}
			else {
				good = false;
				//error message for not providing plaintext with all capital letters
				cout << "\nPlease retype using all CAPITAL letters, thank you." << endl;
				break;
			}
		}
	}

	//converting the key to binary and int
	binconv = bitset<10>(k).to_string();
	decimal = bitset<10>(binconv).to_ulong();	

	//split into two halves
	lhs = (((1 << 5) - 1) & (decimal >> (6 - 1)));
	rhs = (((1 << 5) - 1) & (decimal >> (1 - 1)));	

	perm10 = permutation(binconv, p10, 10);

	//split into two halves
	lhs = (((1 << 5) - 1) & ((bitset<10>(perm10).to_ulong()) >> (6 - 1)));
	rhs = (((1 << 5) - 1) & ((bitset<10>(perm10).to_ulong()) >> (1 - 1)));

	//left circular shift by 1 bit for both sides
	lhs = circLeftShift(lhs, 1);
	rhs = circLeftShift(rhs, 1);	

	perm8 += bitset<5>(lhs).to_string();
	perm8 += bitset<5>(rhs).to_string();
	
	k1 = permutation(perm8, k1, 8);	

	//split into two halves
	lhs = (((1 << 5) - 1) & ((bitset<10>(perm8).to_ulong()) >> (6 - 1)));	
	rhs = (((1 << 5) - 1) & ((bitset<10>(perm8).to_ulong()) >> (1 - 1)));
	
	//left circular shift by 2 bits for both sides
	lhs = circLeftShift(lhs, 2);
	rhs = circLeftShift(rhs, 2);

	newPerm += bitset<5>(lhs).to_string();
	newPerm += bitset<5>(rhs).to_string();
	k2 = permutation(newPerm, k2, 8);

	for (int i = 0; i < plaintxt.length(); i++)	{
		for (int j = 0; j < 2; j++) {
			ipPerm = "";
			ipPerm = permutation(bitset<8>(plaintxt[i]).to_string(), ipPerm, 1);

			lhs = rhs = 0;
			//split into two halves
			lhs = (((1 << 4) - 1) & ((bitset<8>(ipPerm).to_ulong()) >> (5 - 1)));
			rhs = (((1 << 4) - 1) & ((bitset<8>(ipPerm).to_ulong()) >> (1 - 1)));
			ipRight = rhs;
			ipLeft = lhs;

			rhs = ((rhs << 4));
			expPerm = permutation(bitset<8>(rhs).to_string(), expPerm, 9);

			xor = bitset<8>(expPerm).to_ulong() ^ bitset<8>(k1).to_ulong();

			//split into two halves
			lhs = (((1 << 4) - 1) & ((bitset<8>(xor).to_ulong()) >> (5 - 1)));
			rhs = (((1 << 4) - 1) & ((bitset<8>(xor).to_ulong()) >> (1 - 1)));

			lhsRow = permutation(bitset<4>(lhs).to_string(), lhsRow, 2);

			lhsColumn = permutation(bitset<4>(lhs).to_string(), lhsColumn, 3);

			s0box = permutation(lhsRow, lhsColumn, 5);

			rhsRow = permutation(bitset<4>(rhs).to_string(), rhsRow, 2);

			rhsColumn = permutation(bitset<4>(rhs).to_string(), rhsColumn, 3);
			s1box = permutation(rhsRow, rhsColumn, 6);

			sResult += s0box;
			sResult += s1box;

			perm4 = permutation(sResult, perm4, 4);

			xor = bitset<4>(ipLeft).to_ulong() ^ bitset<4>(perm4).to_ulong();

			newPerm = "";
			newPerm += bitset<4>(xor).to_string();
			newPerm += bitset<4>(ipRight).to_string();

			//split into two halves
			newPermLeft = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (5 - 1)));
			newPermRight = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (1 - 1)));

			newPermLeft = newPermLeft + newPermRight;
			newPermRight = newPermLeft - newPermRight;
			newPermLeft = newPermLeft - newPermRight;

			newPerm = "";
			newPerm += bitset<4>(newPermLeft).to_string();
			newPerm += bitset<4>(newPermRight).to_string();

			//split into two halves
			newPermLeft = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (5 - 1)));
			newPermRight = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (1 - 1)));

			expPerm = "";
			expPerm = permutation(bitset<4>(newPermRight).to_string(), expPerm, 9);

			xor = bitset<8>(expPerm).to_ulong() ^ bitset<8>(k2).to_ulong();

			//split into two halves
			lhs = (((1 << 4) - 1) & ((bitset<8>(xor).to_ulong()) >> (5 - 1)));
			rhs = (((1 << 4) - 1) & ((bitset<8>(xor).to_ulong()) >> (1 - 1)));

			lhsRow = lhsColumn = "";
			lhsRow = permutation(bitset<4>(lhs).to_string(), lhsRow, 2);

			lhsColumn = permutation(bitset<4>(lhs).to_string(), lhsColumn, 3);

			s0box = permutation(lhsRow, lhsColumn, 5);

			rhsRow = rhsColumn = "";
			rhsRow = permutation(bitset<4>(rhs).to_string(), rhsRow, 2);

			rhsColumn = permutation(bitset<4>(rhs).to_string(), rhsColumn, 3);

			s1box = permutation(rhsRow, rhsColumn, 6);

			sResult = "";
			sResult += s0box;
			sResult += s1box;

			perm4 = "";

			perm4 = permutation(sResult, perm4, 4);

			lhs = rhs = 0;
			//split into two halves
			lhs = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (5 - 1)));
			rhs = (((1 << 4) - 1) & ((bitset<8>(newPerm).to_ulong()) >> (1 - 1)));
			ipRight = rhs;
			ipLeft = lhs;

			xor = bitset<4>(ipLeft).to_ulong() ^ bitset<4>(perm4).to_ulong();

			newPerm = "";
			newPerm += bitset<4>(xor).to_string();
			newPerm += bitset<4>(ipRight).to_string();
		}

		if (i == 0)
			cout << "\nHere is the cyphertext in hexadecimal format" << endl;

		if (i == (plaintxt.length() - 1)) {
			invIP = permutation(bitset<8>(newPerm).to_string(), invIP, 7);			
			cout << hex << bitset<8>(invIP).to_ulong();			
		}
		else {
			cout << hex << bitset<8>(newPerm).to_ulong();			
		}		
	}
	
	cout << endl;
    return 0;
}


string permutation(string key, string perm, int num) {	
	switch (num) {
	case 1: {
		int IPArray[8] = {2,6,3,1,4,8,5,7};
		for (int i = 0; i < 8; ++i) {
			perm += key[IPArray[i] - 1];
		}
	}
			break;
	case 2: {
		int rowArray[4] = { 1,4 };
		for (int i = 0; i < 2; ++i) {
			perm += key[rowArray[i] - 1];
		}
	}
			break;
	case 3: {
		int colArray[4] = { 2,3 };
		for (int i = 0; i < 2; ++i) {
			perm += key[colArray[i] - 1];
		}
	}
			break;
	case 4: {
		int P4[4] = {2,4,3,1};
		for (int i = 0; i < 4; ++i)	{
			perm += key[P4[i] - 1];
		}
	}
			break;
	case 5: {
		int S0[4][4] = {1,0,3,2,  
						3,2,1,0,
						0,2,1,3,
						3,1,0,2};
		int temp = S0[bitset<8>(key).to_ulong()][bitset<8>(perm).to_ulong()];
		perm = bitset<2>(temp).to_string();
	}
			break;
	case 6: {
		int S1[4][4] = {0,1,2,3,  
						2,0,1,3,
						3,0,1,2,
						2,1,0,3};
		int temp = S1[bitset<8>(key).to_ulong()][bitset<8>(perm).to_ulong()];
		perm = bitset<2>(temp).to_string();
	}
			break;
	case 7: {
		int InvIPArray[8] = { 4,1,3,5,7,2,8,6 };
		for (int i = 0; i < 8; ++i) {
			perm += key[InvIPArray[i] - 1];
		}
	}
			break;
	case 8: {
		int P8_table[8] = {6,3,7,4,8,5,10,9};
		for (int i = 0; i < 8; ++i)	{
			perm += key[P8_table[i] - 1];
		}
	}
			break;
	case 9: {
		int E_P[8] = { 4,1,2,3,2,3,4,1 };
		for (int i = 0; i < 8; ++i) {
			perm += key[E_P[i] - 1];
		}
	}
			 break;
	case 10: {
		int P10_table[10] = {3,5,2,7,4,10,1,9,8,6};
		for (int i = 0; i < 10; ++i) {
			perm += key[P10_table[i] - 1];
		}
	}
			break;	
	}
	return perm;
}

int circLeftShift(unsigned int n, unsigned int m) {
	return ((n << m) | (n >> (5 - m)));
}