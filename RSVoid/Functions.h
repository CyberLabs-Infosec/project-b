#pragma once

#include<vector>
#include"gmpxx.h"
#include"classes.h"

using namespace std;

void common_modulus_attack(mpz_t n, mpz_t e1, mpz_t e2, mpz_t ct1, mpz_t ct2);

unsigned int contd_fraction_convergents(mpz_t x, mpz_t y, vector<Integer>* n, vector<Integer>* d);
void weiner_attack(mpz_t n, mpz_t e, mpz_t c);

void small_e_multiple_ciphertexts(unsigned int e);
void small_e_single_ciphertext(unsigned int e);