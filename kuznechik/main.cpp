#include <iostream>
#include <bitset>
#include <string>
#include <cassert>

#include "pi.h"
#include "block.h"


int main() {
    auto x = Block<8>("10010100");
    auto y = Block<8>("00000111");
    auto z = Block<8 * 8>(std::string(8 * 8 - 9, '0') + "111000011");
    auto r = multiply(x, y, z);
    std::cout << r.get_string() << std::endl;

    return 0;
}
