//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_COMBINATORICS_H
#define LOTTERY_COMBINATORICS_H

#include <bitset>
#include <vector>

std::vector<std::vector<int32_t>> computeBinomialCoefficients(int n);

template <int N> std::vector<std::bitset<N>> computeAllCombinations(int k);

#include "../src/combinatorics.tpp"

#endif //LOTTERY_COMBINATORICS_H
