//
// Created by 佘崧林 on 2019/12/26.
//

#include "../include/Aes.h"
#include "AesConst.h"
#include "BitsetMethod.tpp"

bitset128 Aes::Encrypt(bitset128 m) {
    auto state = new Squre4Marix(m);

    this->AddRoundKey(state, 0);
    for (int i = 1; i < 10; i++) {
        this->RoundEncrypt(state, i);
    }
    state->ByteSubstitution(SBOX);
    state->ShiftRows();
    this->AddRoundKey(state, 10);

    bitset128 cipher = state->collapse();
    delete state;
    return cipher;
}

void Aes::KeyExpansion(bitset128 key) {
    roundKey[0] = Squre4Marix(key);

    for (int i = 1; i <= 10; i++) {
        bitset32 rows[4] = {0x00};
        for (int j = 0; j < 4; ++j) {
            rows[0] <<= 8;
            rows[0] |= roundKey[i - 1][0][j] ^ SBOX[roundKey[i - 1][3][(j + 1) % 4]];
        }
        rows[0] ^= RCON[i] << 3u * 8;
        for (int j = 1; j < 4; ++j) {
            rows[j] = rows[j - 1] ^ roundKey[i - 1].row(j);
        }
        roundKey[i] = Squre4Marix(rows, true);
    }
}

void Aes::AddRoundKey(Squre4Marix *state, uint8_t round) {
    assert(round >= 0 && round <= 10);
    state->ForEach([this, round](int r, int c, uint8_t *data) {
        *data ^= (this->roundKey[round][r][c]);
    });
}

void Aes::RoundEncrypt(Squre4Marix *state, uint8_t round) {
    assert(round > 0 && round < 10);
    state->ByteSubstitution(SBOX);
    state->ShiftRows();
    state->MixColumns();
    this->AddRoundKey(state, round);
}

