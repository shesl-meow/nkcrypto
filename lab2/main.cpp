#include <iostream>
#include <numeric>
#include "Des.h"
#include "TestCase.h"
#include "src/BitsetMethod.tpp"

using namespace std;

int main() {
    static auto avg = [](std::vector<size_t> v) -> double {
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    };
    for (const auto & testCase : testCases) {
        auto key = BitsetMethod::convertFrom<64>((void *) testCase.key, 8);
        auto rplain = BitsetMethod::convertFrom<64>((void *) testCase.txt, 8);
        auto rcipher = BitsetMethod::convertFrom<64>((void *) testCase.out, 8);
        cout << "InitKey:\t" << key << endl;
        cout << "PlainText:\t" << rplain << endl;
        cout << "CipherText:\t" << rcipher << endl;

        Des *des = new Des(key);
        switch (testCase.mode) {
            case DES_ENCRYPT: {
                auto cipher = des->Encode(rplain);
                cout << "CalcCipher:\t" << rcipher << endl;

                auto avalanche = des->AvalancheTestEnc(rplain);
                cout << "Avalance test: (Average " << avg(avalanche) << ")\t" << endl;
                for (auto av: avalanche) cout << av << " ";
                cout << endl;
            }
                break;
            case DES_DECRYPT: {
                auto plain = des->Decode(rcipher);
                cout << "CalcPlain:\t" << plain << endl;

                auto avalanche = des->AvalancheTestDec(rcipher);
                cout << "Avalance test: (Average " << avg(avalanche) << ")\t" << endl;
                for (auto av: avalanche) cout << av << " ";
                cout << endl;
            }
                break;
            default:
                assert(false);
        }
        delete des;
        cout << std::string(64, '-') << endl;
    }
    return 0;
}