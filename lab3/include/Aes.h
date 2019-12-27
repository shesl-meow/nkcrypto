//
// Created by 佘崧林 on 2019/12/26.
//

#ifndef LAB3_AES_H
#define LAB3_AES_H

#include <bitset>
#include <vector>
#include "../src/Squre4Marix.h"

#define bitset128 std::bitset<128>

class Aes {
private:
    bitset128 rawKey;
    Squre4Marix roundKey[11] = {};

public:
    explicit Aes(bitset128 key): rawKey(key) { this->KeyExpansion(key); }

    bitset128 Encrypt(bitset128 m);

    bitset128 Decrypt(bitset128 c);

private:
    void KeyExpansion(bitset128 key);

    void AddRoundKey(Squre4Marix *state, uint8_t round);

    void RoundEncrypt(Squre4Marix *state, uint8_t round);

    void RoundDecrypt(Squre4Marix *state, uint8_t round);

public:
    std::vector<size_t> AvalancheTestEnc(bitset128 m);

    std::vector<size_t> AvalancheTestDec(bitset128 c);
};


#endif //LAB3_AES_H
