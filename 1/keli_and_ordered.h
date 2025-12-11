#ifndef KELI_AND_ORDERED_H
#define KELI_AND_ORDERED_H

#include <bitset>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

std::string dec_to_bin(int);

std::vector<std::string> _div(std::string);

bool _comparison(std::vector<int>, std::vector<std::string>, int&, int& );

std::array<std::array<int,16>,16> algorithm(std::vector<int>, std::vector<int>);

bool is_ordered(int, int);

std::array<std::array<int,16>,16> construct_ordered();

#endif