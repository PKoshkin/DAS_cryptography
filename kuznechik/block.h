#pragma once

#include <bitset>
#include <string>
#include <deque>
#include <cassert>

#include <iostream>


std::deque<std::bitset<8>> get_parts(const std::bitset<128>&);

std::bitset<128> concatinate(const std::deque<std::bitset<8>>);
