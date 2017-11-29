#include "kuznechik.h"


Block encrypt(const Key key, Block block, const MultiplyData& multiply_data) {
    std::array<Block, 10> keys = get_keys(key, multiply_data);
    for (std::size_t i = 0; i < 9; ++i) {
        block = LSX(keys[i], block, multiply_data);
    }
    return X(keys[9], block);
}

Block decrypt(const Key key, Block block, const MultiplyData& multiply_data) {
    std::array<Block, 10> keys = get_keys(key, multiply_data);
    for (int i = 9; i >= 1; --i) {
        block = LSX_inverse(keys[i], block, multiply_data);
    }
    return X(keys[0], block);
}
