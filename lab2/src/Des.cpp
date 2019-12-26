//
// Created by 佘崧林 on 2019/12/25.
//

#include "../include/Des.h"
#include "DesConst.h"
#include "BitsetMethod.tpp"

bitset64 Des::Encode(bitset64 m) {
    bitset64 m_1 = BitsetMethod::reverse<64, 64>(m, IP_1);
    bitset32 m_H = BitsetMethod::slice<64, 32>(m_1, 32, 32),
            m_L = BitsetMethod::slice<64, 32>(m_1, 0, 32);
    for (auto round : finalKey) {
        m_H ^= f(m_L, round);
        std::swap(m_H, m_L);
    }
    return BitsetMethod::reverse<64, 64>(BitsetMethod::merge<32, 32>(m_L, m_H), IP_2);
}

bitset64 Des::Decode(bitset64 c) {
    bitset64 c_1 = BitsetMethod::reverse<64, 64>(c, IP_1);
    bitset32 c_H = BitsetMethod::slice<64, 32>(c_1, 32, 32),
            c_L = BitsetMethod::slice<64, 32>(c_1, 0, 32);
    for (int round = 0; round < 16; round++) {
        c_H ^= f(c_L, finalKey[15 - round]);
        std::swap(c_H, c_L);
    }
    return BitsetMethod::reverse<64, 64>(BitsetMethod::merge<32, 32>(c_L, c_H), IP_2);
}

void Des::updateFinalKey(bitset64 k) {
    static const int move_times[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    bitset56 k_1 = BitsetMethod::reverse<64, 56>(k, PC_1);
    bitset28 k_c = BitsetMethod::slice<56, 28>(k_1, 28, 28),
            k_d = BitsetMethod::slice<56, 28>(k_1, 0, 28);

    for (int round = 0; round < 16; round++) {
        k_c = BitsetMethod::shiftLR<28>(k_c, move_times[round]);
        k_d = BitsetMethod::shiftLR<28>(k_d, move_times[round]);
        finalKey[round] = BitsetMethod::reverse<56, 48>(BitsetMethod::merge<28, 28>(k_c, k_d), PC_2);
    }
}

bitset32 Des::f(bitset32 R, bitset48 Key) {
    bitset48 num_xor = BitsetMethod::reverse<32, 48>(R, E) ^ Key;
    bitset32 S;
    uint64_t x = 8;
    for (int i = 0; i < 8; i++) {
        int i6 = i * 6;
        int row = num_xor[47 - i6] * 2 + num_xor[47 - i6 - 5];
        int col = num_xor[47 - i6 - 1] * 8 + num_xor[47 - i6 - 2] * 4 + num_xor[47 - i6 - 3] * 2 + num_xor[47 - i6 - 4];
        uint64_t num = S_Box[i][row][col];
        S |= (num & 0xfu) << (--x * 4);
    }
    return BitsetMethod::reverse<32, 32>(S, P);
}

std::vector<size_t> Des::AvalancheTestEnc(bitset64 m) {
    this->updateFinalKey(rawKey);
    bitset64 cipher, rawcipher = this->Encode(m);
    std::vector<size_t > result;
    for (size_t i = 0; i < 64; ++i) {
        bitset64 mask = 1llu << i;
        this->updateFinalKey(rawKey ^ mask);
        cipher = this->Encode(m);
        result.push_back((cipher ^ rawcipher).count());
    }
    this->updateFinalKey(rawKey);
    return result;
}

std::vector<size_t> Des::AvalancheTestDec(bitset64 c) {
    this->updateFinalKey(rawKey);
    bitset64 cipher, rawcipher = this->Decode(c);
    std::vector<size_t > result;
    for (size_t i = 0; i < 64; ++i) {
        bitset64 mask = 1llu << i;
        this->updateFinalKey(rawKey ^ mask);
        cipher = this->Decode(c);
        result.push_back((cipher ^ rawcipher).count());
    }
    this->updateFinalKey(rawKey);
    std::reverse(result.begin(), result.end());
    return result;
}

