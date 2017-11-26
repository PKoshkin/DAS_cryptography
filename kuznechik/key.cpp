#include "key.h"


std::pair<Block, Block> F(const Block k, const Block a_1, const Block a_0, const MultiplyData& multiply_data) {
    Block a_1_copy;
    std::copy(a_1.begin(), a_1.end(), a_1_copy.begin());
    Block lsx = LSX(k, a_1_copy, multiply_data);
    lsx[0] ^= a_0[0];
    lsx[1] ^= a_0[1];
    lsx[2] ^= a_0[2];
    lsx[3] ^= a_0[3];
    lsx[4] ^= a_0[4];
    lsx[5] ^= a_0[5];
    lsx[6] ^= a_0[6];
    lsx[7] ^= a_0[7];
    lsx[8] ^= a_0[8];
    lsx[9] ^= a_0[9];
    lsx[10] ^= a_0[10];
    lsx[11] ^= a_0[11];
    lsx[12] ^= a_0[12];
    lsx[13] ^= a_0[13];
    lsx[14] ^= a_0[14];
    lsx[15] ^= a_0[15];
    return std::make_pair(lsx, a_1);
}


std::array<Block, 10> get_keys(const Key key, const MultiplyData& multiply_data) {
    std::array<Block, 10> result;

    std::copy_n(key.begin() + 16, 16, result[0].begin());
    std::copy_n(key.begin(), 16, result[1].begin());

    Block constant = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::pair<Block, Block> keys = std::make_pair(result[0], result[1]);
    for (std::size_t j = 1; j <= 8; ++j) {
        constant[0] = j;
        keys = F(L(constant, multiply_data), keys.first, keys.second, multiply_data);
    }
    result[2] = keys.first;
    result[3] = keys.second;

    for (std::size_t j = 9; j <= 16; ++j) {
        constant[0] = j;
        keys = F(L(constant, multiply_data), keys.first, keys.second, multiply_data);
    }
    result[4] = keys.first;
    result[5] = keys.second;

    for (std::size_t j = 17; j <= 24; ++j) {
        constant[0] = j;
        keys = F(L(constant, multiply_data), keys.first, keys.second, multiply_data);
    }
    result[6] = keys.first;
    result[7] = keys.second;

    for (std::size_t j = 25; j <= 32; ++j) {
        constant[0] = j;
        keys = F(L(constant, multiply_data), keys.first, keys.second, multiply_data);
    }
    result[8] = keys.first;
    result[9] = keys.second;

    return result;
}
