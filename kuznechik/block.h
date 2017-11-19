#pragma once

#include <bitset>
#include <string>
#include <deque>
#include <cassert>

typedef std::bitset<128> Block;
typedef std::bitset<8> SmallBlock;
typedef std::bitset<15> ProductBlock;
typedef std::deque<std::bitset<8>> SplitedBlock;

SplitedBlock get_parts(const Block&);

Block concatinate(const SplitedBlock&);
