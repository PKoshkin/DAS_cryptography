#include "key.h"


std::pair<Block, Block> F(const Block k, const Block a_1, const Block a_0) {
    Block a_1_copy;
    std::copy(a_1.begin(), a_1.end(), a_1_copy.begin());
    Block lsx = LSX(k, a_1_copy);
    for (std::size_t i = 0; i < 16; ++i) {
        lsx[i] ^= a_0[i];
    }
    return std::make_pair(lsx, a_1);
}


std::array<Block, 10> get_keys(const Key key) {
    std::array<Block, 10> result;

    std::copy_n(key.begin() + 16, 16, result[0].begin());
    std::copy_n(key.begin(), 16, result[1].begin());

    std::size_t counter = 2;
    Block constant = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (std::size_t i = 1; i <= 4; ++i) {
        std::pair<Block, Block> keys = std::make_pair(result[2 * i - 2], result[2 * i - 1]);
        for (std::size_t j = 8 * (i - 1) + 1; j <= 8 * (i - 1) + 8; ++j) {
            constant[0] = j;
            keys = F(constant, keys.first, keys.second);
        }
        result[counter++] = keys.first;
        result[counter++] = keys.second;
    }

    return result;
}
