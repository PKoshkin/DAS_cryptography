#include "lsx.h"


Block X(const Block k, Block a) {
    for (std::size_t i = 0; i < 16; ++i) {
        a[i] ^= k[i];
    }
    return a;
}


Block L(Block a, const Data& data) {
    for (std::size_t i = 0; i < 16; ++i) {
        a = R(a, data);
    }
    return a;
}

Block L_fast(Block a, const Data& data) {
    Block result;
    for(std::size_t i = 0; i < 16; ++i) {
        std::uint8_t component = 0;
        for (std::size_t j = 0; j < 16; ++j) {
            component ^= fast_multiply(data.L_matrix[i][j], a[j], data);
        }
        result[i] = component;
    }
    return result;
}

Block L_inverse(Block a, const Data& data) {
    for (std::size_t i = 0; i < 16; ++i) {
        a = R_inverse(a, data);
    }
    return a;
}

Block L_inverse_fast(Block a, const Data& data) {
    Block result;
    for(std::size_t i = 0; i < 16; ++i) {
        std::uint8_t component = 0;
        for (std::size_t j = 0; j < 16; ++j) {
            component ^= fast_multiply(data.L_inverse_matrix[i][j], a[j], data);
        }
        result[i] = component;
    }
    return result;
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


Block R(Block a, const Data& data) {
    std::uint8_t mixed = l(a, data);
    for (std::size_t i = 0; i <= 14; ++i) { // Идем до предпоследнего
        a[i] = a[i + 1];
    }
    a[15] = mixed;
    return a;
}

Block R_inverse(Block a, const Data& data) {
    std::uint8_t a_15 = a[15];
    for (int i = 15; i >= 1; --i) { // Идем до предпоследнего
        a[i] = a[i - 1];
    }
    a[0] = a_15;
    a[0] = l(a, data);
    return a;
}


Block LSX(const Block k, Block a, const Data& data) {
    return L_fast(S(X(k, a)), data);
}

Block LSX_inverse(const Block k, Block a, const Data& data) {
    return S_inverse(L_inverse_fast(X(k, a), data));
}
