#include "lsx.h"


Block X(const Block k, Block a) {
    a[0] ^= k[0];
    a[1] ^= k[1];
    a[2] ^= k[2];
    a[3] ^= k[3];
    a[4] ^= k[4];
    a[5] ^= k[5];
    a[6] ^= k[6];
    a[7] ^= k[7];
    a[8] ^= k[8];
    a[9] ^= k[9];
    a[10] ^= k[10];
    a[11] ^= k[11];
    a[12] ^= k[12];
    a[13] ^= k[13];
    a[14] ^= k[14];
    a[15] ^= k[15];
    return a;
}


Block L(Block a, const MultiplyData& multiply_data) {
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    a = R(a, multiply_data);
    return a;
}

Block L_inverse(Block a, const MultiplyData& multiply_data) {
<<<<<<< HEAD
    for (std::size_t i = 0; i < 16; ++i) {
        a = R_inverse(a, multiply_data);
    }
=======
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
    a = R_inverse(a, multiply_data);
>>>>>>> master
    return a;
}


Block S(Block a) {
    a[0] = pi(a[0]);
    a[1] = pi(a[1]);
    a[2] = pi(a[2]);
    a[3] = pi(a[3]);
    a[4] = pi(a[4]);
    a[5] = pi(a[5]);
    a[6] = pi(a[6]);
    a[7] = pi(a[7]);
    a[8] = pi(a[8]);
    a[9] = pi(a[9]);
    a[10] = pi(a[10]);
    a[11] = pi(a[11]);
    a[12] = pi(a[12]);
    a[13] = pi(a[13]);
    a[14] = pi(a[14]);
    a[15] = pi(a[15]);
    return a;
}

Block S_inverse(Block a) {
    a[0] = pi_inverse(a[0]);
    a[1] = pi_inverse(a[1]);
    a[2] = pi_inverse(a[2]);
    a[3] = pi_inverse(a[3]);
    a[4] = pi_inverse(a[4]);
    a[5] = pi_inverse(a[5]);
    a[6] = pi_inverse(a[6]);
    a[7] = pi_inverse(a[7]);
    a[8] = pi_inverse(a[8]);
    a[9] = pi_inverse(a[9]);
    a[10] = pi_inverse(a[10]);
    a[11] = pi_inverse(a[11]);
    a[12] = pi_inverse(a[12]);
    a[13] = pi_inverse(a[13]);
    a[14] = pi_inverse(a[14]);
    a[15] = pi_inverse(a[15]);
    return a;
}


Block R(Block a, const MultiplyData& multiply_data) {
    unsigned short mixed = l(a, multiply_data);
    a[0] = a[1];
    a[1] = a[2];
    a[2] = a[3];
    a[3] = a[4];
    a[4] = a[5];
    a[5] = a[6];
    a[6] = a[7];
    a[7] = a[8];
    a[8] = a[9];
    a[9] = a[10];
    a[10] = a[11];
    a[11] = a[12];
    a[12] = a[13];
    a[13] = a[14];
    a[14] = a[15];
    a[15] = mixed;
    return a;
}

Block R_inverse(Block a, const MultiplyData& multiply_data) {
    unsigned short a_15 = a[15];
    a[15] = a[14];
    a[14] = a[13];
    a[13] = a[12];
    a[12] = a[11];
    a[11] = a[10];
    a[10] = a[9];
    a[9] = a[8];
    a[8] = a[7];
    a[7] = a[6];
    a[6] = a[5];
    a[5] = a[4];
    a[4] = a[3];
    a[3] = a[2];
    a[2] = a[1];
    a[1] = a[0];
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
