#pragma once

#include <string>
#include <bitset>
#include <cassert>
#include <array>

typedef std::array<unsigned short, 16> Block;
typedef std::array<unsigned short, 32> Key;

Block block_from_string(const std::string&);
Key key_from_string(const std::string&);

std::string to_string(const Block);
