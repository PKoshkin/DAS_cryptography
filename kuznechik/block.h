#pragma once

#include <bitset>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>

#include <iostream>


template <std::size_t BLOCK_SIZE>
class Block {
private:
    std::bitset<BLOCK_SIZE> bitset;

public:
    Block();
    Block(std::string);
    Block(std::size_t);

    std::string get_string() const;
    std::size_t get_number() const;

    std::size_t get_deg() const;

    // multiplying as polynoms
    template <std::size_t MULT_BLOCK_SIZE>
    friend Block<MULT_BLOCK_SIZE> multiply(const Block<MULT_BLOCK_SIZE>&,
                                           const Block<MULT_BLOCK_SIZE>&,
                                           const Block<MULT_BLOCK_SIZE * 2>&);
};


template <std::size_t BLOCK_SIZE>
Block<BLOCK_SIZE>::Block(): bitset() {}


template <std::size_t BLOCK_SIZE>
Block<BLOCK_SIZE>::Block(std::string in_string): bitset(in_string) {
    assert(in_string.length() == BLOCK_SIZE);
}


template <std::size_t BLOCK_SIZE>
Block<BLOCK_SIZE>::Block(std::size_t in_number): bitset(in_number) {
    assert(in_number < pow(2, BLOCK_SIZE));
}


template <std::size_t BLOCK_SIZE>
std::string Block<BLOCK_SIZE>::get_string() const {
    return bitset.to_string();
}


template <std::size_t BLOCK_SIZE>
std::size_t Block<BLOCK_SIZE>::get_number() const {
    return static_cast<std::size_t>(bitset.to_ulong());
}


template <std::size_t BLOCK_SIZE>
std::size_t Block<BLOCK_SIZE>::get_deg() const {
    std::size_t deg = BLOCK_SIZE - 1;
    for (; deg > 0; deg -= 1) {
        if (bitset[deg] == 1) {
            return deg;
        }
    }
}


template <std::size_t BLOCK_SIZE>
Block<BLOCK_SIZE> multiply(const Block<BLOCK_SIZE>& block_1,
                           const Block<BLOCK_SIZE>& block_2,
                           const Block<BLOCK_SIZE * 2>& denominator_block) {
    Block<BLOCK_SIZE * 2> dividend_block;
    for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
        for (std::size_t j = 0; j < BLOCK_SIZE; ++j) {
            if ((block_1.bitset[i] * block_2.bitset[j]) % 2) {
                dividend_block.bitset[i + j].flip();
            }
        }
    }

    Block<BLOCK_SIZE> result;
    int deg_diff = dividend_block.get_deg() - denominator_block.get_deg();
    while (deg_diff >= 0) {
        result.bitset[deg_diff] = 1;
        dividend_block.bitset ^= (denominator_block.bitset << deg_diff);
        deg_diff = dividend_block.get_deg() - denominator_block.get_deg();
    }

    return result;
}


std::vector<Block<8>> get_parts(const Block<128>&);
