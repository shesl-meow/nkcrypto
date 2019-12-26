//
// Created by 佘崧林 on 2019/12/25.
//

#ifndef DES_H
#define DES_H

#include <bitset>
#include <vector>

#define bitset64 std::bitset<64>
#define bitset56 std::bitset<56>
#define bitset28 std::bitset<28>
#define bitset48 std::bitset<48>
#define bitset32 std::bitset<32>

typedef enum {
    DES_DECRYPT, DES_ENCRYPT,
} ENC_MODE;

class Des {
private:
    bitset64 rawKey;
    bitset48 finalKey[16];

    void updateFinalKey(bitset64 k);

    bitset32 f(bitset32 R, bitset48 Key);

public:
    explicit Des(bitset64 k): rawKey(k) { this->updateFinalKey(k); }

    bitset64 Encode(bitset64 m);

    bitset64 Decode(bitset64 c);

    std::vector<size_t> AvalancheTestEnc(bitset64 m);

    std::vector<size_t> AvalancheTestDec(bitset64 c);
};


#endif // lab2_DES_H
