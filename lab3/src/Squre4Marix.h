//
// Created by 佘崧林 on 2019/12/26.
//

#ifndef AES_SQURE4MARIX_H
#define AES_SQURE4MARIX_H

#include <bitset>
#include <functional>

#define bitset32 std::bitset<32>
#define bitset128 std::bitset<128>

#define SQROW 4
#define SQCOL 4

class Squre4Marix {
private:
    uint8_t data[SQROW][SQCOL] = {0x00};
public:
    Squre4Marix() = default;

    explicit Squre4Marix(bitset128 src);

    explicit Squre4Marix(bitset32 src[4], bool isrow = true);

    bitset128 collapse() const;

    bitset32 column(int index) const;

    bitset32 row(int index) const;

    Squre4Marix &Transpose();

    Squre4Marix &ShiftRows();

    Squre4Marix &MixColumns();

    Squre4Marix &ForEach(const std::function<void(int, int, uint8_t *)> &f);

    const uint8_t *operator[](int ind) const {
        return static_cast<const uint8_t *>(this->data[ind]);
    }

    Squre4Marix &operator=(const Squre4Marix &given) {
        return this->ForEach([given](int r, int c, uint8_t *d) { *d = given[r][c]; });
    }
};

#endif //AES_SQURE4MARIX_H
