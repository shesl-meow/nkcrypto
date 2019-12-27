#include <iostream>
#include <Aes.h>
#include <numeric>
#include "TestCase.h"
#include "src/BitsetMethod.tpp"

int main() {
    static auto avg = [](std::vector<size_t> v) -> double {
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    };
    for (auto testCase : testCases) {
        bitset128 key = BitsetMethod::convertFrom<128>(testCase.key, 8);
        bitset128 plain = BitsetMethod::convertFrom<128>(testCase.plain, 8);
        bitset128 cipher = BitsetMethod::convertFrom<128>(testCase.cipher, 8);

        auto aes = new Aes(key);
        auto calc_cipher = aes->Encrypt(plain);
        auto calc_plain = aes->Decrypt(cipher);
        auto avalanche_enc = aes->AvalancheTestEnc(plain);
        auto avalanche_dec = aes->AvalancheTestDec(cipher);

        std::cout << std::string(128, '-') << std::endl;
        std::cout << "Initial Key:\t" << key << std::endl;
        std::cout << "Test Plain :\t" << plain << std::endl;
        std::cout << "Test Cipher:\t" << cipher << std::endl;
        std::cout << "Calc Plain :\t" << calc_plain << std::endl;
        std::cout << "Calc Cipher:\t" << calc_cipher << std::endl;

        std::cout << std::string(128, '#') << std::endl;
        std::cout << "Encrypt avalanche test: (Average " << avg(avalanche_enc) << ")" << std::endl;
        for (int i = 0; i < 64; ++i) std::cout << avalanche_enc[i] << ",";
        std::cout << std::endl;
        for (int i = 64; i < 128; ++i) std::cout << avalanche_enc[i] << ",";
        std::cout << std::endl;

        std::cout << "Decrypt avalanche test: (Average " << avg(avalanche_dec) << ")" << std::endl;
        for (int i = 0; i < 64; ++i) std::cout << avalanche_dec[i] << ",";
        std::cout << std::endl;
        for (int i = 64; i < 128; ++i) std::cout << avalanche_dec[i] << ",";
        std::cout << std::endl;
    }
    return 0;
}