#pragma once

#include <bitset>

#include "block.h"
#include "data.h"

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


std::uint8_t fast_multiply(const std::uint8_t, const std::uint8_t, const MultiplyData&);

std::uint8_t multiply(const std::uint8_t, const std::uint8_t);

std::uint8_t get_mod(std::bitset<15>, std::bitset<15>);
