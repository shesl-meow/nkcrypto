//
// Created by 佘崧林 on 2019/12/27.
//

#include "../include/Rsa.h"
#import <ctime>

Rsa::Rsa(mpz_class prime_p, mpz_class prime_q, mpz_class pow_e) {
    mpz_inits(p, q, e, NULL);
    mpz_set(p, prime_p.get_mpz_t());
    mpz_set(q, prime_q.get_mpz_t());
    mpz_set(e, pow_e.get_mpz_t());

    mpz_t phi;
    mpz_inits(n, phi, d, NULL);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1), mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_add_ui(p, p, 1), mpz_add_ui(q, q, 1);
    mpz_invert(d, e, phi);
    mpz_clear(phi);
}

mpz_class Rsa::Encrypt(mpz_class m) {
    mpz_t c; mpz_init(c);
    mpz_powm(c, m.get_mpz_t(), e, n);
    mpz_class cipher = mpz_class(c);
    mpz_clear(c);
    return cipher;
}

mpz_class Rsa::Decrypt(mpz_class c) {
    mpz_t m; mpz_init(m);
    mpz_powm(m, c.get_mpz_t(), d, n);
    mpz_class message = mpz_class(m);
    mpz_clear(m);
    return message;
}

mpz_class Rsa::GeneratePrime(size_t nbits) {
    static time_t seed;
    static gmp_randstate_t random_state;
    if (!seed) {
        seed = time(nullptr);
        gmp_randinit_mt(random_state);
        gmp_randseed_ui(random_state, seed);
    }

    mpz_t prime; mpz_init(prime);
    mpz_urandomb(prime, random_state, nbits);
    mpz_nextprime(prime, prime);

    mpz_class result = mpz_class(prime);
    mpz_clear(prime);
    return mpz_class(prime);
}
