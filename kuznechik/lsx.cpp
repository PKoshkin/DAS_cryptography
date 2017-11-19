#include "lsx.h"


SplitedBlock& X(const SplitedBlock& k, SplitedBlock& a) {
    assert(k.size() == 16);
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a[i] ^= k[i];
    }
    return a;
}


SplitedBlock& L(SplitedBlock& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a = R(a);
    }
    return a;
}

SplitedBlock& L_inverse(SplitedBlock& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a = R_inverse(a);
    }
    return a;
}


SplitedBlock& S(SplitedBlock& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = pi(a[i]);
    }
    return a;
}

SplitedBlock& S_inverse(SplitedBlock& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = pi_inverse(a[i]);
    }
    return a;
}


SplitedBlock& R(SplitedBlock& a) {
    assert(a.size() == 16);

    SmallBlock mixed = l(a);
    a.pop_front();
    a.push_back(mixed);

    assert(a.size() == 16);
    return a;
}

SplitedBlock& R_inverse(SplitedBlock& a) {
    assert(a.size() == 16);

    SmallBlock a_15 = a.back();
    a.pop_back();
    a.push_front(a_15);
    SmallBlock mixed = l(a);
    a.pop_front();
    a.push_front(mixed);

    assert(a.size() == 16);
    return a;
}


SplitedBlock& LSX(const SplitedBlock& k, SplitedBlock& a) {
    assert(k.size() == 16);
    assert(a.size() == 16);
    return L(S(X(k, a)));
}

SplitedBlock& LSX_inverse(const SplitedBlock& k, SplitedBlock& a) {
    assert(k.size() == 16);
    assert(a.size() == 16);
    return S_inverse(L_inverse(X(k, a)));
}
