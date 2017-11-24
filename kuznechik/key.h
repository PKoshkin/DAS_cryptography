#pragma once

#include <utility> //  для std::pair
#include <array>
#include <algorithm>

#include "block.h"
#include "lsx.h" // Нужно L для генерации констант.


std::pair<Block, Block> F(const Block, const Block, const Block);

std::array<Block, 10> get_keys(const Key);
