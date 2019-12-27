#include <iostream>
#include "include/Rsa.h"

int main() {
    auto p = Rsa::GeneratePrime(512);
    auto q = Rsa::GeneratePrime(512);
    auto e = mpz_class(0x10001);
    auto rsa = new Rsa(p, q, e);

    auto plain = mpz_class(0x10);
    auto cipher = rsa->Encrypt(plain);
    auto deplain = rsa->Decrypt(cipher);
    std::cout << plain.get_str(16) << std::endl;
    std::cout << cipher.get_str(16) << std::endl;
    std::cout << deplain.get_str(16) << std::endl;
    return 0;
}