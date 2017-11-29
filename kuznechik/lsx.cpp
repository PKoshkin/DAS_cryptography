#include "lsx.h"


Block X(const Block k, Block a) {
    for (std::size_t i = 0; i < 16; ++i) {
        a[i] ^= k[i];
    }
    return a;
}


Block L(Block a, const MultiplyData& multiply_data) {
    for (std::size_t i = 0; i < 16; ++i) {
        a = R(a, multiply_data);
    }
    return a;
}

Block L_inverse(Block a, const MultiplyData& multiply_data) {
    for (std::size_t i = 0; i < 16; ++i) {
        a = R_inverse(a, multiply_data);
    }
    return a;
}


Block S(Block a) {
    for (std::size_t i = 0; i < 16; ++i) {
        a[i] = pi(a[i]);
    }
    return a;
}

Block S_inverse(Block a) {
    for (std::size_t i = 0; i < 16; ++i) {
        a[i] = pi_inverse(a[i]);
    }
    return a;
}


Block R(Block a, const MultiplyData& multiply_data) {
    unsigned short mixed = l(a, multiply_data);
    for (std::size_t i = 0; i <= 14; ++i) { // Идем до предпоследнего
        a[i] = a[i + 1];
    }
    a[15] = mixed;
    return a;
}

Block R_inverse(Block a, const MultiplyData& multiply_data) {
    unsigned short a_15 = a[15];
    for (int i = 15; i >= 1; --i) { // Идем до предпоследнего
        a[i] = a[i - 1];
    }
    a[0] = a_15;
    a[0] = l(a, multiply_data);
    return a;
}


Block LSX(const Block k, Block a, const MultiplyData& multiply_data) {
    return L(S(X(k, a)), multiply_data);
}

Block LSX_inverse(const Block k, Block a, const MultiplyData& multiply_data) {
    return S_inverse(L_inverse(X(k, a), multiply_data));
}
