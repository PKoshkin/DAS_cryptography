#pragma once

#include <utility> //  для std::pair
#include <vector>
#include <deque>

#include "block.h"


std::pair<SplitedBlock, SplitedBlock> F(const SplitedBlock&, const SplitedBlock&, const SplitedBlock&);
