#pragma once

#include <utility> //  для std::pair
#include <vector>
#include <deque>
#include <bitset>

#include "block.h"
#include "lsx.h" // Нужно L для генерации констант.


std::vector<SplitedBlock> get_constants();

std::pair<SplitedBlock, SplitedBlock> F(const SplitedBlock&, const SplitedBlock&, const SplitedBlock&);

std::vector<SplitedBlock> get_keys(const std::bitset<256>&);
