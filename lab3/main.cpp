#include <iostream>
#include <Aes.h>

int main() {
    Aes *aes = new Aes(0x1234);
    bitset128 cipher = aes->Encrypt(0x1234);
    std::cout << cipher.to_string() << std::endl;
    bitset128 plain = aes->Decrypt(cipher);
    std::cout << plain.to_string() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}