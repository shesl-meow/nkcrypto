//
// Created by 佘崧林 on 2019/12/28.
//

#ifndef LAB5_MD5HASH_H
#define LAB5_MD5HASH_H

#include <bitset>

#define bitset128 std::bitset<128>
#define bitset512 std::bitset<512>

class Md5Hash {
public:
    // default ctor, just initailize
    Md5Hash() { this->init(); }

    explicit Md5Hash(const std::string &text);

    void init();

    void update(const unsigned char *buf, size_t length);

    void update(const char *buf, size_t length);

    Md5Hash &finalize();

    std::string hexdigest() const;

private:
    void transform(const uint8_t block[64u]);

    bool finalized = false;
    uint8_t buffer[64u]{};      // bytes that didn't fit in last 64 byte chunk
    bitset512 pblock;
    uint32_t count[2] = {0, 0};     // 64bit counter for number of bits (lo, hi)
    bitset128 digest;

    // low level logic operations
    // F, G, H and I are basic MD5 functions.
    static inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }

    static inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }

    static inline uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }

    static inline uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | ~z); }

    // rotate_left rotates x left n bits.
    static inline uint32_t rotate_left(uint32_t x, uint32_t n) { return (x << n) | (x >> (32 - n)); }

    // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
    // Rotation is separate from addition to prevent recomputation.
    static inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
    }

    static inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
    }

    static inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
    }

    static inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
        a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
    }

public:
    static std::string md5hash(const std::string &str) { return Md5Hash(str).hexdigest(); }
};


#endif //LAB5_MD5HASH_H
