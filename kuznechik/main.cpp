#include <iostream>
#include <bitset>
#include <string>
#include <cassert>

#include "pi.h"
#include "polynom.h"


int main() {
    auto x = std::bitset<8>("10010100");
    auto y = std::bitset<8>("00000111");
    auto z = std::bitset<8 * 2>(std::string(8 * 2 - 9, '0') + "111000011");
    auto r = multiply(x, y, z);
    std::cout << r.to_string() << std::endl;

    return 0;
}
