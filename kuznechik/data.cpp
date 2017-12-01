#include "data.h"


MultiplyData::MultiplyData(std::string multiply_map_file_name) {
    std::ifstream multiply_map_file(multiply_map_file_name);
    for (std::size_t i = 0; i < 256; ++i) {
        for (std::size_t j = 0; j < 256; ++j) {
            unsigned short tmp;
            multiply_map_file >> tmp;
            multiply_map[i][j] = static_cast<std::uint8_t>(tmp);
        }
    }
}
