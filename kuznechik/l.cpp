#include "l.h"


unsigned short l(const Block in_block) {
    unsigned short coefs[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    unsigned short denominator(451); // 111000011
    unsigned short sum = 0;
    for (std::size_t i = 0; i < 16; ++i) {
        unsigned short product = multiply(coefs[i], in_block[i]);
        sum ^= product;
    }
    return get_mod(sum, denominator);
}
