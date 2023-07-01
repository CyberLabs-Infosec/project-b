#pragma once

#include"gmpxx.h"
#include<vector>

using namespace std;

void common_modulus_attack(mpz_t n, mpz_t e1, mpz_t e2, mpz_t ct1, mpz_t ct2);

unsigned int contd_fraction_convergents(mpz_t x, mpz_t y, vector<mpz_t>* n, vector<mpz_t>* d);
void weiner_attack(mpz_t n, mpz_t e, mpz_t c);