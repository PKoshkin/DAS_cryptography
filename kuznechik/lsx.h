#pragma once

#include <cassert>

#include "l.h"
#include "pi.h"
#include "block.h"
#include "data.h"

#include <iostream>


Block X(const Block, Block);

Block L(Block, const MultiplyData&);
Block L_inverse(Block, const MultiplyData&);

Block S(Block);
Block S_inverse(Block);

Block R(Block, const MultiplyData&);
Block R_inverse(Block, const MultiplyData&);

Block LSX(const Block, Block, const MultiplyData&);
Block LSX_inverse(const Block, Block, const MultiplyData&);
