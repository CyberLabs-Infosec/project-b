#include<iostream>
#include"Functions.h"
#include"gmpxx.h"

using namespace std;


void common_modulus_attack(mpz_t n, mpz_t e1, mpz_t e2, mpz_t ct1, mpz_t ct2)
{
	if (mpz_sgn(e1) == 0 || mpz_sgn(e2) == 0)
	{
		cout << "One public exponent is zero. This condition is not allowed." << endl;
	}
	else if(mpz_sgn(e1) == -1 || mpz_sgn(e2) == -1)
	{
		cout << "One public exponent is less than zero. This condition is not allowed." << endl;
	}
	else
	{
		mpz_t exp_gcd, n_gcd;
		mpz_t comp;
		mpz_inits(comp, exp_gcd, n_gcd, NULL);
		mpz_set_ui(comp, 1);
		mpz_gcd(exp_gcd, e1, e2);
		cout << "\nGCD of exponents is " << exp_gcd << endl;
		mpz_gcd(n_gcd, ct2, n);
		cout << "GCD of ct2 and n is " << n_gcd << endl;

		if (mpz_cmp(exp_gcd, comp) != 0 || mpz_cmp(n_gcd, comp) != 0)
		{
			cout << "Common Modulus attack is not possible.";
			return;
		}

		mpz_t s, t;
		mpz_inits(s, t, NULL);
		mpz_gcdext(exp_gcd, s, t, e1, e2);
		mpz_t ct1_inv, ct2_inv;
		mpz_inits(ct1_inv, ct2_inv, NULL);
		mpz_invert(ct1_inv, ct1, n);
		mpz_invert(ct2_inv, ct2, n);

		mpz_t p1, p2;
		mpz_inits(p1, p2, NULL);
		if (mpz_sgn(s) == -1)
		{
			mpz_neg(s, s);
			unsigned long int s2, t2;
			s2 = mpz_get_ui(s);
			t2 = mpz_get_ui(t);
			mpz_pow_ui(p1, ct1_inv, s2);
			mpz_pow_ui(p2, ct2, t2);
			if (mpz_cmp_ui(s, s2) == 0 && mpz_cmp_ui(t, t2) == 0)
			{
				mpz_t m;
				mpz_init(m);
				mpz_mul(m, p1, p2);      //m is the plaintext message

				cout << "The plaintext message is : ";
				mpz_out_str(NULL, 10, m);
			}
		}
		else if (mpz_sgn(t) == -1)
		{
			mpz_neg(t, t);
			unsigned long int s2, t2;
			s2 = mpz_get_ui(s);
			t2 = mpz_get_ui(t);
			mpz_pow_ui(p1, ct1, s2);
			mpz_pow_ui(p2, ct2_inv, t2);
			if (mpz_cmp_ui(s, s2) == 0 && mpz_cmp_ui(t, t2) == 0)
			{
				mpz_t m;
				mpz_init(m);
				mpz_mul(m, p1, p2);      //m is the plaintext message

				cout << "The plaintext message is : ";
				mpz_out_str(NULL, 10, m);
			}
		}

	}
	return;
}


