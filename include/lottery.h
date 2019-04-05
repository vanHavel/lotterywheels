//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_LOTTERY_H
#define LOTTERY_LOTTERY_H

#include <bitset>
#include <unordered_map>
#include <vector>

template <uint32_t N> std::vector<std::vector<uint32_t>> computeDrawToGroupEdges(
        const std::vector<std::bitset<N>> &draws,
        int t,
        const std::unordered_map<std::bitset<N>, uint32_t> &groupToId
);

template <uint8_t N> bool verifyTCoverage(
        const std::vector<std::bitset<N>> &samples,
        const std::vector<std::bitset<N>> &cover,
        int t
);

uint32_t computeDrawCoverage(
        const std::vector<uint32_t> &cover,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw,
        std::vector<uint32_t> &coverage
);

uint32_t removeTicketFromCover(
        std::vector<uint32_t> &coverage,
        uint32_t ticketID,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw
);

uint32_t addTicketToCover(
        std::vector<uint32_t> &coverage,
        uint32_t ticketID,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw
);

#include "../src/lottery.tpp"

#endif //LOTTERY_LOTTERY_H
