#include "l.h"


std::uint8_t l(const Block in_block, const Data& data) {
    std::uint8_t coefs[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    std::uint8_t sum = 0;
    for (std::size_t i = 0; i < 16; ++i) {
        sum ^= fast_multiply(coefs[i], in_block[i], data);
    }
    return sum;
}
