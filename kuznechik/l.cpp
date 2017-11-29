#include "l.h"


unsigned short l(const Block in_block, const MultiplyData& multiply_data) {
    unsigned short coefs[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    unsigned short denominator(451); // 111000011
    unsigned short sum = 0;
    sum ^= multiply(coefs[0], in_block[0], multiply_data);
    sum ^= multiply(coefs[1], in_block[1], multiply_data);
    sum ^= multiply(coefs[2], in_block[2], multiply_data);
    sum ^= multiply(coefs[3], in_block[3], multiply_data);
    sum ^= multiply(coefs[4], in_block[4], multiply_data);
    sum ^= multiply(coefs[5], in_block[5], multiply_data);
    sum ^= multiply(coefs[6], in_block[6], multiply_data);
    sum ^= multiply(coefs[7], in_block[7], multiply_data);
    sum ^= multiply(coefs[8], in_block[8], multiply_data);
    sum ^= multiply(coefs[9], in_block[9], multiply_data);
    sum ^= multiply(coefs[10], in_block[10], multiply_data);
    sum ^= multiply(coefs[11], in_block[11], multiply_data);
    sum ^= multiply(coefs[12], in_block[12], multiply_data);
    sum ^= multiply(coefs[13], in_block[13], multiply_data);
    sum ^= multiply(coefs[14], in_block[14], multiply_data);
    sum ^= multiply(coefs[15], in_block[15], multiply_data);
    return sum;
}
