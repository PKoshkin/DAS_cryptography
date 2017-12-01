#pragma once

#include <array>
#include <string>
#include <fstream>
#include <cstdint>


struct Data {
    std::array<std::array<std::uint8_t, 256>, 256> multiply_map;
    std::array<std::array<std::uint8_t, 16>, 16> L_matrix;
    std::array<std::array<std::uint8_t, 16>, 16> L_inverse_matrix;

    Data(std::string, std::string, std::string);
};
