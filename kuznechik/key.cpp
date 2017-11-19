#include "key.h"


std::vector<SplitedBlock> get_constants() {
    std::vector<SplitedBlock> result;
    result.reserve(32);
    for (std::size_t i = 1; i <= 32; ++i) {
        SplitedBlock splited_block = split(Block(i));
        result.push_back(L(splited_block));
    }
    return result;
}


std::pair<SplitedBlock, SplitedBlock> F(const SplitedBlock& k, const SplitedBlock& a_1, const SplitedBlock& a_0) {
    SplitedBlock a_1_copy = a_1;
    SplitedBlock lsx = LSX(k, a_1_copy);
    assert(lsx.size() == 16);
    for (std::size_t i = 0; i < lsx.size(); ++i) {
        lsx[i] ^= a_0[i];
    }
    return std::make_pair(lsx, a_1);
}


std::vector<SplitedBlock> get_keys(const std::bitset<256>& key) {
    std::vector<SplitedBlock> result;
    result.reserve(10);
    std::vector<SplitedBlock> constnts = get_constants();
    result.push_back(split(Block(key.to_string().substr(0, 128))));
    result.push_back(split(Block(key.to_string().substr(128, 256))));
    for (std::size_t i = 1; i <= 4; ++i) {
        std::pair<SplitedBlock, SplitedBlock> keys = std::make_pair(result[2 * i - 2], result[2 * i - 1]);
        for (std::size_t j = 8 * (i - 1) + 1; j <= 8 * (i - 1) + 8; ++j) {
            keys = F(constnts[j - 1], keys.first, keys.second);
        }
        result.push_back(keys.first);
        result.push_back(keys.second);
    }
    assert(result.size() == 10);
    return result;
}
