//
// Created by 佘崧林 on 2019/12/26.
//

#ifndef LAB3_AES_H
#define LAB3_AES_H

#include <bitset>
#include "../src/Squre4Marix.h"

#define bitset8 std::bitset<8>
#define bitset128 std::bitset<128>

class Aes {
private:
    Squre4Marix roundKey[11] = {};

public:
    explicit Aes(bitset128 key) { this->KeyExpansion(key); }

    bitset128 Encrypt(bitset128 m);

    bitset128 Decrypt(bitset128 c);

    void *Cipher(void *input, int length = 0);

    void *InvCipher(void *input, int length);

private:
    void KeyExpansion(bitset128 key);

    void AddRoundKey(Squre4Marix *state, uint8_t round);

    void RoundEncrypt(Squre4Marix *state, uint8_t round);

    void RoundDecrypt(Squre4Marix *state, uint8_t round);
};


#endif //LAB3_AES_H
