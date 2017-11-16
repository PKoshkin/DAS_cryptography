#include <iostream>
#include <bitset>
#include <string>
#include <cassert>

#include "pi.h"


int main() {
    std::string bit_string;
    std::cin >> bit_string;
    assert(bit_string.length() == 8);
    std::string pi_of_bit_string = pi(bit_string);
    std::cout << pi_of_bit_string << std::endl;
    return 0;
}
