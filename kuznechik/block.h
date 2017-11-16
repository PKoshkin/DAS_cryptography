#pragma once

#include <bitset>
#include <string>
#include <cassert>
#include <cmath>
#include <memory>
#include <vector>


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

std::unique_ptr<Block<8>[]> get_parts(const Block<128>&);
