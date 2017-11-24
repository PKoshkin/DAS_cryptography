#include "kuznechik.h"


Block encrypt(const Key key, Block block) {
    std::array<Block, 10> keys = get_keys(key);
    for (std::size_t i = 0; i < 9; ++i) {
        block = LSX(keys[i], block);
    }
    return X(keys[9], block);
}

Block decrypt(const Key key, Block block) {
    std::array<Block, 10> keys = get_keys(key);
    for (int i = 9; i >= 1; --i) {
        block = LSX_inverse(keys[i], block);
    }
    return X(keys[0], block);
}
