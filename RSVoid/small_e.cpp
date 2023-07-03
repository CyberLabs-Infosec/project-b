#include<iostream>
#include<vector>
#include"gmpxx.h"
#include"Functions.h"
#include"classes.h"

using namespace std;


void small_e_multiple_ciphertexts(unsigned int e)
{
	vector<Integer> cipher(e);
	vector<Integer> n(e);

	cout << "\n\tEnter the ciphertexts and corresponding moduli: ";
	for (int j = 0; j < e; j++)
	{
		mpz_t ciphertext, modulus;
		mpz_inits(ciphertext, modulus, NULL);
		mpz_inits(cipher.at(j).var, n.at(j).var, NULL);
		cout << "\n\t\tCipher: ";
		cin >> ciphertext;
		cout << "\t\tModulus: ";
		cin >> modulus;
		mpz_set(cipher.at(j).var, ciphertext);
		mpz_set(n.at(j).var, modulus);
		mpz_clear(ciphertext);
		mpz_clear(modulus);
	}

	for (int i = 0; i < e-1; i++)
	{
		for (int j = i+1; j < e; j++)
		{
			mpz_t gcdval;
			mpz_init(gcdval);
			mpz_gcd(gcdval, n.at(i).var, n.at(j).var);
			if (mpz_cmp_ui(gcdval, 1) != 0)
			{
				cout << "\tThe moduli are not all pairwise coprime." << endl;
				mpz_t cipher1;
				mpz_init(cipher1);
				mpz_set(cipher1, cipher.at(i).var);

				mpz_t p, q, phi, d, exp;
				mpz_inits(p, q, phi, d, exp, NULL);
				mpz_gcd(p, n.at(i).var, n.at(j).var);
				mpz_tdiv_q(q, n.at(i).var, p);
				mpz_sub_ui(p, p, 1);
				mpz_sub_ui(q, q, 1);
				mpz_mul(phi, p, q);
				mpz_set_ui(exp, e);
				mpz_invert(d, exp, phi);

				mpz_t message;
				mpz_init(message);
				mpz_powm(message, cipher1, d, n.at(i).var);
				cout << "\nThe message is: \n\t" << message << endl;

				return;
			}
			else
			{
				continue;
			}
		}
	}

	vector<Integer> terms(e);
	mpz_t common_c, moduli_product;
	mpz_inits(common_c, moduli_product, NULL);
	mpz_set_ui(common_c, 0);
	mpz_set_ui(moduli_product, 1);

	for (int j = 0; j < e; j++)
	{
		mpz_t p, q;
		mpz_inits(p, q, NULL);
		mpz_set_ui(p, 1);
		mpz_set_ui(q, 1);
		for (int k = 0; k < e; k++)
		{
			if (k != j)
			{
				mpz_mul(p, p, n.at(k).var);
			}
		}
		mpz_invert(q, p, n.at(j).var);
		mpz_init(terms.at(j).var);
		mpz_mul(terms.at(j).var, p, q);
		mpz_mul(terms.at(j).var, terms.at(j).var, cipher.at(j).var);
		mpz_add(common_c, common_c, terms.at(j).var);

		mpz_mul(moduli_product, moduli_product, n.at(j).var);
	}

	mpz_mod(common_c, common_c, moduli_product);

	mpz_t message;
	mpz_init(message);
	mpz_root(message, common_c, e);

	cout << "\nThe message is: \n\t" << message << endl;
}



void small_e_single_ciphertext(unsigned int e)
{
	cout << "\nWarning! This is a brute-force method and it may not work. Use this method only if the public exponent is very small." << endl;

	mpz_t cipher, n, message;
	mpz_inits(cipher, n, message, NULL);

	cout << "\n\tCiphertext: ";
	cin >> cipher;
	cout << "\tModulus: ";
	cin >> n;

	unsigned int k = 0;
	while (1)
	{
		mpz_t temp;
		mpz_init(temp);

		mpz_mul_ui(temp, n, k);
		mpz_add(temp, temp, cipher);
		if (mpz_root(temp, temp, e) == 0)
		{
			mpz_clear(temp);
			continue;
		}
		else
		{
			mpz_set(message, temp);
			cout << "\nThe message is: \n\t" << message << endl;
			
			break;
		}
	}
}