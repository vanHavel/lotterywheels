//
// Created by Lukas Huwald on 2019-04-05.
//

#ifndef LOTTERY_UTILS_H
#define LOTTERY_UTILS_H

#include <bitset>
#include <random>
#include <unordered_map>
#include <vector>

template <uint8_t N> std::unordered_map<std::bitset<N>, uint32_t> computeInverseMapping(std::vector<std::bitset<N>> vec);

template <uint8_t N> std::bitset<N> removeIthMember(const std::bitset<N> bitset, int index);

template <uint8_t N> std::bitset<N> addRandomMember(
        const std::bitset<N> bitset,
        std::uniform_int_distribution<uint8_t> universeDistribution,
        std::mt19937 &generator
);

#include "../src/utils.tpp"

#endif //LOTTERY_UTILS_H
