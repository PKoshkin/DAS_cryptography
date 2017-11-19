#pragma once

#include <bitset>
#include <deque>
#include <cassert>

#include "l.h"
#include "pi.h"
#include "block.h"


SplitedBlock& X(const SplitedBlock&, SplitedBlock&);

SplitedBlock& L(SplitedBlock&);
SplitedBlock& L_inverse(SplitedBlock&);

SplitedBlock& S(SplitedBlock&);
SplitedBlock& S_inverse(SplitedBlock&);

SplitedBlock& R(SplitedBlock&);
SplitedBlock& R_inverse(SplitedBlock&);

SplitedBlock& LSX(const SplitedBlock&, SplitedBlock&);
SplitedBlock& LSX_inverse(const SplitedBlock&, SplitedBlock&);
