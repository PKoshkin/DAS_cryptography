#pragma once

#include <array>

#include "block.h"
#include "key.h"
#include "lsx.h"
#include "data.h"


Block encrypt(const Key, Block, const MultiplyData&);
Block decrypt(const Key, Block, const MultiplyData&);
