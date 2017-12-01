#pragma once

#include <cassert>

#include "l.h"
#include "pi.h"
#include "block.h"
#include "data.h"

#include <iostream>


Block X(const Block, Block);

Block L(Block, const Data&);
Block L_fast(Block, const Data&);
Block L_inverse(Block, const Data&);
Block L_inverse_fast(Block, const Data&);

Block S(Block);
Block S_inverse(Block);

Block R(Block, const Data&);
Block R_inverse(Block, const Data&);

Block LSX(const Block, Block, const Data&);
Block LSX_inverse(const Block, Block, const Data&);
