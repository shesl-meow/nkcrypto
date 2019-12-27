//
// Created by 佘崧林 on 2019/12/26.
//

#include "../include/Aes.h"
#include "AesConst.h"

bitset128 Aes::Encrypt(bitset128 m) {
    auto state = new Squre4Marix(m);

    this->AddRoundKey(state, 0);
    for (int i = 1; i < 10; i++) {
        this->RoundEncrypt(state, i);
    }
    state->ByteSubstitution(SBOX);
    state->ShiftRows(false);
    this->AddRoundKey(state, 10);

    bitset128 cipher = state->collapse();
    delete state;
    return cipher;
}

bitset128 Aes::Decrypt(bitset128 c) {
    auto state = new Squre4Marix(c);

    this->AddRoundKey(state, 10);
    state->ShiftRows(true);
    state->ByteSubstitution(INV_SBOX);
    for (int i = 9; i > 0; i--) {
        this->RoundDecrypt(state, i);
    }
    this->AddRoundKey(state, 0);

    bitset128 plain = state->collapse();
    delete state;
    return plain;
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
    state->ShiftRows(false);
    state->MixColumns(false);
    this->AddRoundKey(state, round);
}

void Aes::RoundDecrypt(Squre4Marix *state, uint8_t round) {
    assert(round > 0 && round < 10);
    this->AddRoundKey(state, round);
    state->MixColumns(true);
    state->ShiftRows(true);
    state->ByteSubstitution(INV_SBOX);
}

std::vector<size_t> Aes::AvalancheTestEnc(bitset128 m) {
    this->KeyExpansion(rawKey);
    bitset128 cipher, rawcipher = this->Encrypt(m);
    std::vector<size_t > result;
    for (size_t i = 0; i < 128; ++i) {
        bitset128 mask = 1llu << i;
        this->KeyExpansion(rawKey ^ mask);
        cipher = this->Encrypt(m);
        result.push_back((cipher ^ rawcipher).count());
    }
    this->KeyExpansion(rawKey);
    return result;
}

std::vector<size_t> Aes::AvalancheTestDec(bitset128 c) {
    this->KeyExpansion(rawKey);
    bitset128 cipher, rawcipher = this->Decrypt(c);
    std::vector<size_t > result;
    for (size_t i = 0; i < 128; ++i) {
        bitset128 mask = 1llu << i;
        this->KeyExpansion(rawKey ^ mask);
        cipher = this->Decrypt(c);
        result.push_back((cipher ^ rawcipher).count());
    }
    this->KeyExpansion(rawKey);
    return result;
}


