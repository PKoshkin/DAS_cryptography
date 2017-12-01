#pragma once

#include <array>
#include <string>
#include <fstream>
#include <cstdint>


struct MultiplyData {
    std::array<std::array<std::uint8_t, 256>, 256> multiply_map;

    MultiplyData(std::string);
};
