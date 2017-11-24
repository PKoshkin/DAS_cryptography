#pragma once

#include <bitset>

#include "block.h"

#include <iostream>


template <std::size_t BLOCK_SIZE>
std::size_t get_deg(const std::bitset<BLOCK_SIZE>& in_polynom) {
    std::size_t deg = BLOCK_SIZE - 1;
    for (; deg > 0; deg -= 1) {
        if (in_polynom[deg] == 1) {
            return deg;
        }
    }
    return 0;
}


unsigned short multiply(const unsigned short, const unsigned short);

unsigned short get_mod(const unsigned short, const unsigned short);
