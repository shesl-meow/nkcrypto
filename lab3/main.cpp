#include <iostream>
#include <Aes.h>

int main() {
    Aes *aes = new Aes(0x1234);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}