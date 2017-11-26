#include "data.h"


MultiplyData::MultiplyData(std::string index_map_file_name, std::string multiply_map_file_name) {
    std::ifstream index_map_file(index_map_file_name);
    std::ifstream multiply_map_file(multiply_map_file_name);
    for (std::size_t i = 0; i < 256; ++i) {
        index_map_file >> index_map[i];
    }
    for (std::size_t i = 0; i < 8; ++i) {
        for (std::size_t j = 0; j < 256; ++j) {
            multiply_map_file >> multiply_map[i][j];
        }
    }
}
