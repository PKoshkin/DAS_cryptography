#include "kuznechik.h"


Block encrypt(const Key key, Block block, const MultiplyData& multiply_data) {
    std::array<Block, 10> keys = get_keys(key, multiply_data);
    block = LSX(keys[0], block, multiply_data);
    block = LSX(keys[1], block, multiply_data);
    block = LSX(keys[2], block, multiply_data);
    block = LSX(keys[3], block, multiply_data);
    block = LSX(keys[4], block, multiply_data);
    block = LSX(keys[5], block, multiply_data);
    block = LSX(keys[6], block, multiply_data);
    block = LSX(keys[7], block, multiply_data);
    block = LSX(keys[8], block, multiply_data);
    return X(keys[9], block);
}

Block decrypt(const Key key, Block block, const MultiplyData& multiply_data) {
    std::array<Block, 10> keys = get_keys(key, multiply_data);
    block = LSX_inverse(keys[9], block, multiply_data);
    block = LSX_inverse(keys[8], block, multiply_data);
    block = LSX_inverse(keys[7], block, multiply_data);
    block = LSX_inverse(keys[6], block, multiply_data);
    block = LSX_inverse(keys[5], block, multiply_data);
    block = LSX_inverse(keys[4], block, multiply_data);
    block = LSX_inverse(keys[3], block, multiply_data);
    block = LSX_inverse(keys[2], block, multiply_data);
    block = LSX_inverse(keys[1], block, multiply_data);
    return X(keys[0], block);
}
