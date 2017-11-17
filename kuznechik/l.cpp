#include "l.h"


Block<128> l(const Block<128>& in_block) {
    auto parts = get_parts(in_block);
    Block<128> result;
    short coefs[16] = {
        148, 32, 133, 16, 194, 192, 1, 251,
        1, 192, 194, 166, 133, 32, 148, 1
    };
    auto denominator = Block<8 * 2>(std::string(8 * 2 - 9, '0') + "111000011");
    for (std::size_t i = 0; i < 16; ++i) {
        Block<8> product = multiply(Block<8>(coefs[i]), parts[i], denominator);
        result ^= 
    }
}
