#include "vec_8.h"


std::string vec_8(const short in_int) {
    return std::bitset<8>(in_int).to_string();
}
