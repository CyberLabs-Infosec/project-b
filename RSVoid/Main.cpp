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

	cout << "\n\nEnter the value of public exponent, e: ";
	unsigned int pub_exp;
	cin >> pub_exp;
	cout << "\tDo you have " << pub_exp << " ciphertexts? (y/n) ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		small_e_multiple_ciphertexts(pub_exp);
	}
	else if(choice == 'n' || choice == 'N')
	{
		small_e_single_ciphertext(pub_exp);
	}
	else
	{
		cout << "\tWrong choice!" << endl;
	}


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

}