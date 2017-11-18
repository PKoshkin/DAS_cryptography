#pragma once

#include <bitset>
#include <deque>
#include <cassert>

#include "l.h"
#include "pi.h"

#include <iostream>


std::deque<std::bitset<8>>& X(const std::deque<std::bitset<8>>&, std::deque<std::bitset<8>>&);

std::deque<std::bitset<8>>& L(std::deque<std::bitset<8>>&);
std::deque<std::bitset<8>>& L_inverse(std::deque<std::bitset<8>>&);

std::deque<std::bitset<8>>& S(std::deque<std::bitset<8>>&);
std::deque<std::bitset<8>>& S_inverse(std::deque<std::bitset<8>>&);

std::deque<std::bitset<8>>& R(std::deque<std::bitset<8>>&);
std::deque<std::bitset<8>>& R_inverse(std::deque<std::bitset<8>>&);
