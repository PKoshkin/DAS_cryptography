#pragma once

#include <string>
#include <bitset>
#include <cassert>
#include <array>
#include <cstdint>

typedef std::array<std::uint8_t, 16> Block;
typedef std::array<std::uint8_t, 32> Key;

Block block_from_string(const std::string&);
Key key_from_string(const std::string&);

std::string to_string(const Block);
