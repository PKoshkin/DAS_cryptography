#include "l.h"

std::vector<std::bitset<8>> get_parts(const std::bitset<128>& in_block) {
    std::vector<std::bitset<8>> result;
    result.reserve(16);
    std::string in_string = in_block.to_string();
    for (std::size_t i = 0; i < 16; ++i) {
        result.emplace_back(in_string.substr(i * 8, 8));
    }
   return result;
}


std::bitset<128> l(const std::bitset<128>& in_block) {
    std::vector<std::bitset<8>> parts = get_parts(in_block);
    std::bitset<128> result;
    short coefs[16] = {
        148, 32, 133, 16, 194, 192, 1, 251,
        1, 192, 194, 166, 133, 32, 148, 1
    };
    std::bitset<8 * 2> denominator = std::bitset<8 * 2>(std::string(8 * 2 - 9, '0') + "111000011");
    for (std::size_t i = 0; i < 16; ++i) {
        std::bitset<8> product = multiply(std::bitset<8>(coefs[i]), parts[i], denominator);
    }
}
