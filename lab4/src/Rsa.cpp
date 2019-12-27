//
// Created by 佘崧林 on 2019/12/27.
//

#include "../include/Rsa.h"

Rsa::Rsa(mpz_class prime_p, mpz_class prime_q, mpz_class pow_e) {
    mpz_inits(p, q, e, NULL);
    mpz_set(p, prime_p.get_mpz_t());
    mpz_set(q, prime_q.get_mpz_t());
    mpz_set(e, pow_e.get_mpz_t());

    mpz_t phi;
    mpz_inits(n, phi, d, NULL);
    mpz_mul(n, p, q);
    mpz_mul(phi, p-1, q-1);
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
    gmp_randstate_t r_state;
    gmp_randinit_default(r_state);
    gmp_randseed_ui(r_state, time(0));

    mpz_t prime; mpz_init(prime);
    mpz_urandomb(prime, r_state, nbits);
    mpz_nextprime(prime, prime);
    return mpz_class(prime);
}
