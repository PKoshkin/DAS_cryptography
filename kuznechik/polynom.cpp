#include "polynom.h"

unsigned short multiply(const unsigned short polynom_1, const unsigned short polynom_2) {
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
    return static_cast<unsigned short>(product_polynom.to_ulong());
}

unsigned short get_mod(const unsigned short dividend, const unsigned short denominator) {
    std::bitset<15> dividend_polynom(dividend);
    std::bitset<15> denominator_polynom(denominator);
    int deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    while (deg_diff >= 0) {
        dividend_polynom ^= (denominator_polynom << deg_diff);
        deg_diff = get_deg(dividend_polynom) - get_deg(denominator_polynom);
    }
    // Остаток, который надо вернуть лежит в dividend_polynom. Только надо отрезать нули в начале.
    return static_cast<unsigned short>(dividend_polynom.to_ulong());
}
