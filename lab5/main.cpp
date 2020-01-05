#include <iostream>
#include <Md5Hash.h>
#include "TestCase.h"

int main() {
    for (auto testCase: testCases) {
        std::string plaintext = std::string(testCase.plaintext);
        std::string hashtext = std::string(testCase.hashtext);
        std::string md5sum = Md5Hash::md5hash(plaintext);

        std::cout << "Raw Text: " << plaintext << std::endl;
        std::cout << "Desired Md5: " << hashtext << std::endl;
        std::cout << "Calc Md5: " << hashtext << std::endl;
    }
    return 0;
}