#include "polynom.h"

std::uint8_t multiply(const std::uint8_t polynom_1, const std::uint8_t polynom_2, const MultiplyData& multiply_data) {
    return multiply_data.multiply_map[polynom_1][polynom_2];
}

std::uint8_t compute_multiply(const std::uint8_t polynom_1, const std::uint8_t polynom_2) {
    assert(polynom_1 < 256);
    assert(polynom_2 < 256);
    std::bitset<8> bitset_1(polynom_1);
    std::bitset<8> bitset_2(polynom_2);
    std::bitset<15> product_polynom;

    for (std::size_t i = 0; i < 8; ++i) {
        for (std::size_t j = 0; j < 8; ++j) {
            if (bitset_1[i] * bitset_2[j]) {
                product_polynom.flip(i + j);
            }
        }
    }

    return get_mod(product_polynom, std::bitset<15>(451));
}

std::uint8_t get_mod(std::bitset<15> dividend_polynom, std::bitset<15> denominator_polynom) {
    int deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    while (deg_diff >= 0) {
        dividend_polynom ^= (denominator_polynom << deg_diff);
        deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    }
    // Остаток, который надо вернуть лежит в dividend_polynom. Только надо отрезать нули в начале.
    return static_cast<std::uint8_t>(dividend_polynom.to_ulong());
}
