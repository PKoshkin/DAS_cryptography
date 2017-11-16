#include <iostream>
#include <bitset>
#include <string>
#include <cassert>
#include <memory>

#include "pi.h"
#include "block.h"


int main() {
    std::string bit_string = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    std::cout << bit_string.length() << std::endl;
    Block<128> block(bit_string);
    std::unique_ptr<Block<8>[]> blocks = get_parts(block);
    for (std::size_t i = 0; i < 16; ++i) {
        std::cout << blocks[i].get_string() << std::endl;
    }
    return 0;
}
