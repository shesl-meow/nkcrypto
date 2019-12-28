//
// Created by 佘崧林 on 2019/12/27.
//

#ifndef LAB4_RSA_H
#define LAB4_RSA_H

#include "gmpxx.h"

class Rsa {
private:
    mpz_t p{}, q{}, d{};

public:
    mpz_t n{}, e{};

    Rsa(mpz_class prime_p, mpz_class prime_q, mpz_class pow_e);

    mpz_class Encrypt(mpz_class m);

    mpz_class Decrypt(mpz_class c);

    static mpz_class GeneratePrime(size_t nbits);
};


#endif //LAB4_RSA_H
