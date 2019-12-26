#include <iostream>
#include "Des.h"
#include "TestCase.h"
#include "src/BitsetMethod.tpp"

using namespace std;

int main() {
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

                cout << "Avalance test:\t";
                auto avalanche = des->AvalancheTestEnc(rplain);
                for (auto av: avalanche) cout << av << " ";
                cout << endl;
            }
                break;
            case DES_DECRYPT: {
                auto plain = des->Decode(rcipher);
                cout << "CalcPlain:\t" << plain << endl;

                cout << "Avalance test:\t";
                auto avalanche = des->AvalancheTestDec(rcipher);
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