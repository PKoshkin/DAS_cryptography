#include "kuznechik.h"


Block encrypt(const Key key, Block block, const Data& data) {
    std::array<Block, 10> keys = get_keys(key, data);
    for (std::size_t i = 0; i < 9; ++i) {
        block = LSX(keys[i], block, data);
    }
    return X(keys[9], block);
}

Block decrypt(const Key key, Block block, const Data& data) {
    std::array<Block, 10> keys = get_keys(key, data);
    for (int i = 9; i >= 1; --i) {
        block = LSX_inverse(keys[i], block, data);
    }
    return X(keys[0], block);
}
