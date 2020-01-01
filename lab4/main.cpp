#include <iostream>
#include "Rsa.h"

int main() {
    auto p = Rsa::GeneratePrime(512);
    auto q = Rsa::GeneratePrime(512);
    auto e = mpz_class(0x10001);
    std::cout << "Generate Random Prime p: " << p.get_str(16) << std::endl;
    std::cout << "Generate Random Prime q: " << q.get_str(16) << std::endl;
    std::cout << "Using Most Common e: " << e.get_str(16) << std::endl;
    std::cout << std::string(32, '-') << std::endl;

    auto rsa = new Rsa(p, q, e);
    auto plain = mpz_class(0x10);
    auto cipher = rsa->Encrypt(plain);
    auto deplain = rsa->Decrypt(cipher);
    std::cout << "Plain Text: " << plain.get_str(16) << std::endl;
    std::cout << "Cipher Text: " << cipher.get_str(16) << std::endl;
    std::cout << "Deplain Text: " << deplain.get_str(16) << std::endl;
    return 0;
}