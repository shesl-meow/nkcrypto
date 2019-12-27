#pragma once

namespace BitsetMethod {
    template<size_t P>
    static inline std::bitset<P> shiftLR(std::bitset<P> srcK, int shift) {
        return (std::bitset<P>) ((srcK << shift) | (srcK >> (P - shift)));
    }

    template<size_t P, size_t Q>
    static inline std::bitset<Q> reverse(std::bitset<P> srcK, const uint8_t table[Q]) {
        std::bitset<Q> result;
        for (size_t i = 0; i < Q; i++)
            result[Q - 1 - i] = srcK[P - table[i]];
        return result;
    }

    template<size_t P, size_t Q>
    static inline std::bitset<Q> slice(std::bitset<P> srcK, unsigned int offset, unsigned int width) {
        unsigned long long mask = (1llu << width) - 1;
        return (std::bitset<Q>) ((srcK >> offset).to_ullong() & mask);
    }

    template<size_t P, size_t Q>
    static inline std::bitset<P + Q> merge(std::bitset<P> hbs, std::bitset<Q> lbs) {
        return (std::bitset<P + Q>) ((hbs.to_ullong() << Q) | lbs.to_ullong());
    }

    template<size_t P>
    static inline std::bitset<P> convertFrom(const void *src, size_t bwidth) {
        std::bitset<P> dst;
        assert(P % bwidth == 0 && bwidth % 8 == 0);
        unsigned long long mask = (1llu << bwidth) - 1;
        for (int round = 0; round * bwidth < P; round++) {
            dst <<= bwidth;
            dst |= *((uint8_t *)src + round * bwidth/8) & mask;
        }
        return dst;
    }
}

