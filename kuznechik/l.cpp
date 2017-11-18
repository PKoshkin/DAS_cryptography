#include "l.h"


std::bitset<8> l(const std::deque<std::bitset<8>>& in_block) {
    short coefs[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    std::bitset<15> denominator = std::bitset<15>(std::string(15 - 9, '0') + "111000011");
    std::bitset<15> sum;
    for (std::size_t i = 0; i < 16; ++i) {
        std::bitset<15> product = multiply(std::bitset<8>(coefs[i]), in_block[i]);
        sum ^= product;
    }

    return get_mod(sum, denominator);
}
