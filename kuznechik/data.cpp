#include "data.h"


Data::Data(std::string multiply_map_file_name, std::string L_matrix_file_name, std::string L_inverse_matrix_file_name) {
    std::ifstream multiply_map_file(multiply_map_file_name);
    for (std::size_t i = 0; i < 256; ++i) {
        for (std::size_t j = 0; j < 256; ++j) {
            unsigned short tmp;
            multiply_map_file >> tmp;
            multiply_map[i][j] = static_cast<std::uint8_t>(tmp);
        }
    }

    std::ifstream L_matrix_file(L_matrix_file_name);
    for (std::size_t i = 0; i < 16; ++i) {
        for (std::size_t j = 0; j < 16; ++j) {
            unsigned short tmp;
            L_matrix_file >> tmp;
            L_matrix[i][j] = static_cast<std::uint8_t>(tmp);
        }
    }

    std::ifstream L_inverse_matrix_file(L_inverse_matrix_file_name);
    for (std::size_t i = 0; i < 16; ++i) {
        for (std::size_t j = 0; j < 16; ++j) {
            unsigned short tmp;
            L_inverse_matrix_file >> tmp;
            L_inverse_matrix[i][j] = static_cast<std::uint8_t>(tmp);
        }
    }
}
