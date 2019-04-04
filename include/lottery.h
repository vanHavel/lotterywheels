//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_LOTTERY_H
#define LOTTERY_LOTTERY_H

#include "combinatorics.h"

template <uint32_t N> std::vector<std::vector<uint32_t>> computeDrawToGroupEdges(
        std::vector<std::bitset<N>> draws,
        int t,
        std::unordered_map<std::bitset<N>, uint32_t> groupToId
);

template <uint32_t N> bool verifyTCoverage(std::vector<std::bitset<N>> samples, std::vector<std::bitset<N>> cover, int t);

std::vector<uint32_t> computeDrawCoverage(
        const std::vector<uint32_t> &cover,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw,
        uint32_t numberOfDraws
);

uint32_t computeUncoveredDrawCount(std::vector<uint32_t> coverage);

#include "../src/lottery.tpp"

#endif //LOTTERY_LOTTERY_H
