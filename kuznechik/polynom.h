#pragma once

#include <bitset>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>

#include <iostream>


template <std::size_t BLOCK_SIZE>
std::size_t get_deg(const std::bitset<BLOCK_SIZE>& in_polynom) {
    std::size_t deg = BLOCK_SIZE - 1;
    for (; deg > 0; deg -= 1) {
        if (in_polynom[deg] == 1) {
            return deg;
        }
    }
}


template <std::size_t BLOCK_SIZE>
std::bitset<BLOCK_SIZE> multiply(const std::bitset<BLOCK_SIZE>& polynom_1,
                           const std::bitset<BLOCK_SIZE>& polynom_2,
                           const std::bitset<BLOCK_SIZE * 2>& denominator_polynom) {
    std::bitset<BLOCK_SIZE * 2> dividend_polynom;
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        for (std::size_t j = 0; j < BLOCK_SIZE; ++j) {
            if ((polynom_1[i] * polynom_2[j]) % 2) {
                dividend_polynom[i + j].flip();
            }
        }
    }

    std::bitset<BLOCK_SIZE> result;
    int deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    while (deg_diff >= 0) {
        result[deg_diff] = 1;
        dividend_polynom ^= (denominator_polynom << deg_diff);
        deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    }

    return result;
}
