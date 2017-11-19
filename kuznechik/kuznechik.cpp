#include "kuznechik.h"


SplitedBlock encrypt(const std::bitset<256>& key, SplitedBlock block) {
    std::vector<SplitedBlock> keys = get_keys(key);
    for (std::size_t i = 0; i < 9; ++i) {
        block = LSX(keys[i], block);
    }
    return X(keys[9], block);
}

SplitedBlock decrypt(const std::bitset<256>& key, SplitedBlock block) {
    std::vector<SplitedBlock> keys = get_keys(key);
    for (int i = 9; i >= 1; --i) {
        block = LSX_inverse(keys[i], block);
    }
    return X(keys[0], block);
}
