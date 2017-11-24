#pragma once

#include <array>

#include "block.h"
#include "key.h"
#include "lsx.h"


Block encrypt(const Key, Block);
Block decrypt(const Key, Block);
