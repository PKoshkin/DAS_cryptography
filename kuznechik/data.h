#pragma once

#include <array>
#include <string>
#include <fstream>


struct MultiplyData {
    std::array<unsigned short, 256> index_map;
    std::array<std::array<unsigned short, 256>, 8> multiply_map;

    MultiplyData(std::string, std::string);
};
