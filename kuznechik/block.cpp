#include "block.h"


std::unique_ptr<Block<8>[]> get_parts(const Block<128>& in_block) {
    std::unique_ptr<Block<8>[]> result = std::make_unique<Block<8>[]>(16);
    std::string in_string = in_block.get_string();
    for (std::size_t i = 0; i < 16; ++i) {
        result[i] = Block<8>(in_string.substr(i * 8, 8));
    }
   return result;
}
