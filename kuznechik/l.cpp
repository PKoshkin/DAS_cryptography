#include "l.h"


SmallBlock l(const SplitedBlock& in_block) {
    assert(in_block.size() == 16);

    short coefs[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    ProductBlock denominator(std::string(15 - 9, '0') + "111000011");
    ProductBlock sum;
    for (std::size_t i = 0; i < 16; ++i) {
        ProductBlock product = multiply(SmallBlock(coefs[i]), in_block[i]);
        sum ^= product;
    }

    return get_mod(sum, denominator);
}
