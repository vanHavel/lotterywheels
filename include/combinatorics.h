//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_COMBINATORICS_H
#define LOTTERY_COMBINATORICS_H

#include <bitset>
#include <vector>

std::vector<std::vector<uint32_t>> computeBinomialCoefficients(int n);

template <uint8_t N> std::vector<std::bitset<N>> computeAllCombinations(int k);

template <uint8_t N> std::vector<std::bitset<N>> computeSubCombinations(const std::bitset<N> &set, int k);

template <uint8_t N> std::vector<std::bitset<N>> computeSuperCombinations(const std::bitset<N> &set, int k);

#include "../src/combinatorics.tpp"

#endif //LOTTERY_COMBINATORICS_H
