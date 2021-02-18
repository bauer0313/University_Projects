//************************************************************** 
// Final Project RSA Encryption System 
// Name:	 Thomas Bauer 
// Class:	 CMPS 4663 - Network Security
// Date:	 05/06/2019 
// Filename: NetSecFinal.cpp
//*************************************************************** 

#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

int main() {
	uint64_t n;				
	uint64_t e;				// encryption key
	uint64_t p;				// one of selected primes
	uint64_t q;				// one of selected primes
	uint64_t d;				// decryption key
	uint64_t f;				// temp variable
	uint64_t C;				// Cypertext
	uint64_t M;				// Plaintext message
	uint64_t t;				// totient of n
	uint64_t s;				// temp variable
	uint64_t v;				// temp variable v to hold d
	p = 61;					// First prime number
	q = 79;					// Second prime number
	n = p*q;				// Value n to be modded
	e = 979;				// exponent
	t = (p - 1)*(q - 1);	// totient of n
	M = 20239981;			// Message
	f = e;					// temp variable f to hold e
	d = 0;					// this is the decryption key
	s = 0;					// temp variable s to hold m


	// find the variable for d such that:
	// e is relatively prime to totient
	// i is less than totient
	// (e x i) mod n = 1
	// this will give us d = i
	for (int i = 1; i < t; i++)	{
		if (((e * i) % t) == 1)
			d = i;		
	}
	cout << "d = " << d << endl;
	v = d;

	// this will find the value for d
	// must pick d so that it is < totient of n
	cout << "Value for d: " << endl;
	for (int i = 0; i < n; i++) {
		if (e*i % t == 1) {			
			cout << i << endl;
		}
	}
	cout << endl;
	
	// verifies that values for M, n, and e 
	// combine to get the correct answer for C
	C = 1;
	while (e > 0) {
		C *= M;
		C %= n;
		e--;
	}

	// verifies that the values for C, d, and n 
	// combine to get the correct answer for M (using s)
	while (d > 0) {
		s *= C;
		s %= n;
		d--;
	}

	//resets e and d after using them to find C and M
	e = f;
	d = v;
	
	cout << "C: " << C << "  d: " << d << "   e: " << e << endl;
	cout << "\nC = M^e mod n" << endl;
	cout << C << " = " << M << " ^ " << e << " % " << n << endl;
	cout << "\nM = C^d mod n" << endl;
	cout << M << " = " << C << " ^ " << d << " % " << n << endl;
    return 0;
}

