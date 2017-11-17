#include "block.h"


std::vector<Block<8>> get_parts(const Block<128>& in_block) {
    std::vector<Block<8>> result;
    result.reserve(16);
    std::string in_string = in_block.get_string();
    for (std::size_t i = 0; i < 16; ++i) {
        result.emplace_back(in_string.substr(i * 8, 8));
    }
   return result;
}
