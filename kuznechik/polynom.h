#pragma once

#include <bitset>

#include "block.h"


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
std::bitset<(BLOCK_SIZE - 1) * 2 + 1> multiply(const std::bitset<BLOCK_SIZE>& polynom_1,
                                               const std::bitset<BLOCK_SIZE>& polynom_2) {
    std::bitset<(BLOCK_SIZE - 1) * 2 + 1> product_polynom;
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        for (std::size_t j = 0; j < BLOCK_SIZE; ++j) {
            if (polynom_1[i] * polynom_2[j]) {
                product_polynom.flip(i + j);
            }
        }
    }
    return product_polynom;
}


template <std::size_t BLOCK_SIZE>
std::bitset<(BLOCK_SIZE - 1) / 2 + 1> get_mod(std::bitset<BLOCK_SIZE> dividend_polynom,
                                              const std::bitset<BLOCK_SIZE>& denominator_polynom) {
    int deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    while (deg_diff >= 0) {
        dividend_polynom ^= (denominator_polynom << deg_diff);
        deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    }
    // Остаток, который надо вернуть лежит в dividend_polynom. Только надо отрезать нули в начале.
    return std::bitset<(BLOCK_SIZE - 1) / 2 + 1>(
        dividend_polynom.to_string().substr(
            (BLOCK_SIZE - 1) / 2, // Начальный символ
            (BLOCK_SIZE) / 2 + 1  // Длина
        )
    );
}
