#pragma once

#include <cassert>

#include "l.h"
#include "pi.h"
#include "block.h"

#include <iostream>


Block X(const Block, Block);

Block L(Block);
Block L_inverse(Block);

Block S(Block);
Block S_inverse(Block);

Block R(Block);
Block R_inverse(Block);

Block LSX(const Block, Block);
Block LSX_inverse(const Block, Block);
