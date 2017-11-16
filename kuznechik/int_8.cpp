#include "int_8.h"


short int_8(const std::string& bit_string) {
    return static_cast<short>(std::bitset<8>(bit_string).to_ulong());
}
