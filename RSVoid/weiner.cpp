#include<iostream>
#include"gmpxx.h"
#include"Functions.h"
#include<vector>

using namespace std;


unsigned int contd_fraction_convergents(mpz_t x, mpz_t y, mpz_t* n, mpz_t* d)          // x is n, y is e
{
	mpz_t rem, q;
	mpz_inits(q, rem, NULL);
	mpz_t z;         //z is zero variable
	mpz_inits(z, NULL);
	mpz_set_ui(z, 0);
	
	//vector<mpz_t> coeff;
	mpz_t* coeff;
	unsigned int size = 0;
	while (mpz_cmp(rem, z) != 0)
	{
		mpz_cdiv_qr(q, rem, x, y);
		//coeff.push_back(q);
		mpz_init(*(coeff + size));
		mpz_set(*(coeff + size), q);
		size++;
		mpz_set(x, y);
		mpz_set(y, rem);	
	}
	
	unsigned int i = 0, j = 0;

	for (i = 1; i <= size; i++)
	{
		mpz_t s, t;
		mpz_inits(s, t, NULL);
		mpz_set(t, coeff[i-1]);
		mpz_set_ui(s, 1);
		for (j = i-1; j >= 1; j--)
		{
			mpz_t temp_t;
			mpz_set(temp_t, t);
			mpz_mul(t, coeff[j], t);
			mpz_add(t, s, t);
			mpz_set(s, temp_t);
		}
		//n->push_back(t);
		//d->push_back(s);
		mpz_inits(n[i - 1], d[i - 1]);
		mpz_set(n[i - 1], t);
		mpz_set(d[i - 1], s);
	}

	for (int i = 0; i < size; i++)
	{
		cout << "\t" << n[i] << "/" << d[i] << endl;
	}


	return size;
}



void weiner_attack(mpz_t n, mpz_t e, mpz_t c)
{
	/*vector<mpz_t> numerator;
	vector<mpz_t> denominator;
	contd_fraction_convergents(n, e, &numerator, &denominator);*/

	mpz_t *numerator, *denominator; 
	//  missing line
	unsigned int size = contd_fraction_convergents(n, e, numerator, denominator);

	unsigned int i, count = 0;

	mpz_t d, k;
	mpz_inits(d, k, NULL);

	for (i = 1; i <= size; i++)
	{
		//mpz_set(d, numerator.at(i));
		//mpz_set(k, denominator.at(i));
		mpz_set(d, numerator[i - 1]);
		mpz_set(k, denominator[i - 1]);
		
		mpz_t even_check, ed;
		mpz_t val0, val1;             //variables for comparison
		mpz_inits(val0, val1, NULL);
		mpz_set_ui(val1, 1);
		mpz_inits(even_check, ed, NULL);
		mpz_mod_ui(even_check, d, 2);
		mpz_mul(ed, e, d);
		mpz_mod(ed, ed, k);

		if (mpz_cmp(even_check, val0) == 0 || mpz_cmp(ed, val1) != 0)
		{
			continue;
		}

		mpz_t phi;
		mpz_init(phi);
		mpz_mul(ed, e, d);
		mpz_sub_ui(phi, ed, 1);
		mpz_cdiv_q(phi, phi, k);

		mpz_t m, m2, n2;
		mpz_inits(m, m2, n2, NULL);
		mpz_sub(m, n, phi);
		mpz_add_ui(m, m, 1);
		mpz_mul_ui(n2, n, 4);
		mpz_pow_ui(m2, m, 2);
		mpz_sub(m2, m2, n2);
		if (mpz_perfect_square_p(m2) == 0)
		{
			continue;
		}
		else
		{
			mpz_sqrt(m2, m2);
		}

		mpz_t p, q;
		mpz_inits(p, q, NULL);
		mpz_add(p, m2, m);
		if (mpz_divisible_ui_p(p, 2) == 0)
		{
			continue;
		}
		else
		{
			mpz_cdiv_q_ui(p, p, 2);
			count = 1;
			mpz_cdiv_q(q, n, p);
		}
	}

	if (count == 0)
	{
		cout << "\nWeiner's Attack failure!" << endl;
	}
	else
	{
		mpz_t message;
		mpz_init(message);
		mpz_powm(message, c, d, n);

		cout << "\nThe value of d is: " << d << endl;
		cout << "\nThe message is: \n" << message << endl;
	}
}

