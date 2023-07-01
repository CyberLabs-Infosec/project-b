/*
	----------------RSVoid----------------

	RSA Breaker: A tool for attacking RSA with all well-known attack algorithms, conidering their efficiency and effectiveness.


*/


#include<iostream>
#include"Functions.h"


using namespace std;


void intro(void);



int main(void)
{
	intro();

	mpz_t n1, e1, e2, ct1, ct2;
	mpz_inits(n1, e1, e2, ct1, ct2, NULL);

	cout << "Enter the values of n, e1, e2, ct1, ct2 respectively: \n";
	//cin >> n1 >> e1 >> e2 >> ct1 >> ct2;
	//common_modulus_attack(n1, e1, e2, ct1, ct2);
	
	mpz_t n, e, c;
	mpz_inits(n, e, c, NULL);
	cin >> n >> e >> c;
	weiner_attack(n, e, c);


	return 0;
}


void intro(void)
{
	cout << "RSVoid: RSA Analyser and Decryptor";

	cout << "\n\nRSVoid implements commonly known methods for attacking weak RSA encryption. Some of the implemented methods are: ";
	cout << "\n\t1. Common Modulus attack";
	cout << "\n\t2. Low encryption exponent";
	cout << "\n\t3. Low decryption exponent";
	cout << "\n\t4. Short pad attack";

	cout << "\n\nEnter key-pair values to run possible attacks";
}