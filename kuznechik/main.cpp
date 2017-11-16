#include <iostream>
#include <bitset>
#include <string>
#include <cassert>

#include "pi.h"
#include "block.h"


int main() {
    std::string bit_string;
    std::cin >> bit_string;
    Block<8> block(bit_string);
    std::string pi_of_bit_string = pi(bit_string).get_string();
    std::cout << pi_of_bit_string << std::endl;
    return 0;
}
