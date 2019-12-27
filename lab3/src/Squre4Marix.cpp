//
// Created by 佘崧林 on 2019/12/26.
//

#include "Squre4Marix.h"

Squre4Marix::Squre4Marix(bitset128 src) {
    static const bitset128 mask = 0xff;
    for (int r = 0; r < SQROW; ++r) {
        bitset128 datasource = src >> ((SQROW - 1 - r) * SQCOL) * 8;
        for (int c = 0; c < SQCOL; ++c) {
            bitset128 d = datasource >> (SQCOL - 1 - c) * 8;
            this->data[r][c] = (d & mask).to_ullong();
        }
    }
}

Squre4Marix::Squre4Marix(bitset32 src[4], bool isrow) {
    static const bitset32 mask = 0xff;
    if (isrow) {
        for (int r = 0; r < SQROW; ++r) {
            for (int c = 0; c < SQCOL; ++c) {
                bitset32 d = src[r] >> (SQCOL - 1 - c) * 8;
                this->data[r][c] = (d & mask).to_ullong();
            }
        }
    } else {
        for (int c = 0; c < SQCOL; ++c) {
            for (int r = 0; r < SQROW; ++r) {
                bitset32 d = src[c] >> (SQROW - 1 - r) * 8;
                this->data[r][c] = (d & mask).to_ullong();
            }
        }
    }
}

bitset128 Squre4Marix::collapse() const {
    bitset128 result;
    for (int r = 0; r < SQROW; ++r) {
        for (int c = 0; c < SQCOL; ++c) {
            result <<= 8;
            result |= this->data[r][c];
        }
    }
    return result;
}

bitset32 Squre4Marix::column(int index) const {
    bitset32 result = 0x0;
    for (auto row : this->data) {
        result <<= 8;
        result |= row[index];
    }
    return result;
}

bitset32 Squre4Marix::row(int index) const {
    bitset32 result = 0x0;
    for (auto ele: this->data[index]) {
        result <<= 8;
        result |= ele;
    }
    return result;
}

Squre4Marix &Squre4Marix::Transpose() {
    for (int r = 0; r < SQROW; ++r) {
        for (int c = r + 1; c < SQCOL; ++c) {
            std::swap(this->data[r][c], this->data[c][r]);
        }
    }
    return *this;
}


Squre4Marix &Squre4Marix::ShiftRows() {
    Squre4Marix temp = *this;
    this->ForEach([temp](int r, int c, uint8_t *element) {
        *element = temp[r][(r + c) % 4];
    });
    return *this;
}

Squre4Marix &Squre4Marix::MixColumns() {
    // learnt from http://cs.ucsb.edu/~koc/cs178/projects/JT/aes.c
    static const auto xtime = [](uint8_t x) -> uint8_t {
        return (x & 0x80u) ? (((x << 1u) ^ 0x1Bu) & 0xFFu) : x << 1u;
    };

    for (auto r : this->data) {
        uint8_t t = r[0] ^r[1] ^r[2] ^r[3], u = r[0];
        r[0] ^= t ^ xtime(r[0] ^ r[1]);
        r[1] ^= t ^ xtime(r[1] ^ r[2]);
        r[2] ^= t ^ xtime(r[2] ^ r[3]);
        r[3] ^= t ^ xtime(r[3] ^ u);
    }
    return *this;
}

Squre4Marix &Squre4Marix::ForEach(const std::function<void(int, int, uint8_t *)> &f) {
    for (int r = 0; r < SQROW; ++r)
        for (int c = 0; c < SQCOL; ++c)
            f(r, c, &(this->data[r][c]));
    return *this;
}


