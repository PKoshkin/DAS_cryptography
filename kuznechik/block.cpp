#include "block.h"


Block block_from_string(const std::string& in_string) {
    assert(in_string.length() == 128);
    Block result;
    for (std::size_t i = 0; i < 16; ++i) {
        result[i] = static_cast<std::uint8_t>(std::bitset<8>(in_string.substr(8 * (15 - i), 8)).to_ulong());
    }
    return result;
}

Key key_from_string(const std::string& in_string) {
    assert(in_string.length() == 256);
    Key result;
    for (std::size_t i = 0; i < 32; ++i) {
        result[i] = static_cast<std::uint8_t>(std::bitset<8>(in_string.substr(8 * (31 - i), 8)).to_ulong());
    }
    return result;
}


std::string to_string(const Block in_block) {
    std::string result;
    for (int i = 15; i >= 0; --i) {
        result += std::bitset<8>(in_block[i]).to_string();
    }
    return result;
}
