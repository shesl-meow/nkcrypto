//
// Created by 佘崧林 on 2019/12/26.
//

#include "../include/Aes.h"
#include "AesConst.h"
#include "BitsetMethod.tpp"

bitset128 Aes::Encrypt(bitset128 m) {
    Squre4Marix state = Squre4Marix(m).Transpose();

    state.ForEach([this](int r, int c, uint8_t *data) {
        *data ^= (this->roundKey[0][r][c]);
    }); // AddRoundKey

    for (int i = 1; i < 11; i++) {
        state.ForEach([](int r, int c, uint8_t *data) {
            *data = SBOX[*data];
        }); // ByteSubstitution

        state.ShiftRows();
        if (i != 10) state.MixColumns();

        state.ForEach([this, i](int r, int c, uint8_t *data) {
            *data ^= (this->roundKey[i][r][c]);
        }); // AddRoundKey
    }
    return state.Transpose().collapse();
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



