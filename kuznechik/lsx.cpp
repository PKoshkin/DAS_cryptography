#include "lsx.h"


std::deque<std::bitset<8>>& X(const std::deque<std::bitset<8>>& k, std::deque<std::bitset<8>>& a) {
    assert(k.size() == 16);
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a[i] ^= k[i];
    }
    return a;
}


std::deque<std::bitset<8>>& L(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a = R(a);
    }
    return a;
}

std::deque<std::bitset<8>>& L_inverse(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < 16; ++i) {
        a = R(a);
    }
    return a;
}


std::deque<std::bitset<8>>& S(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = pi(a[i]);
    }
    return a;
}

std::deque<std::bitset<8>>& S_inverse(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = pi_inverse(a[i]);
    }
    return a;
}


std::deque<std::bitset<8>>& R(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    std::bitset<8> mixed = l(a);
    a.pop_front();
    a.push_back(mixed);

    assert(a.size() == 16);
    return a;
}

std::deque<std::bitset<8>>& R_inverse(std::deque<std::bitset<8>>& a) {
    assert(a.size() == 16);

    std::bitset<8> a_15 = a.back();
    a.pop_back();
    a.push_front(a_15);
    std::bitset<8> mixed = l(a);
    a.pop_front();
    a.push_front(mixed);

    assert(a.size() == 16);
    return a;
}
