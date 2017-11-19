#pragma once

#include <vector>

#include "block.h"
#include "key.h"
#include "lsx.h"


SplitedBlock encrypt(const std::bitset<256>&, SplitedBlock);
SplitedBlock decrypt(const std::bitset<256>&, SplitedBlock);
