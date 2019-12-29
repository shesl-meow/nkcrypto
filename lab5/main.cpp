#include <iostream>
#include <Md5Hash.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << Md5Hash::md5hash(std::string("Hello World")) << std::endl;
    return 0;
}