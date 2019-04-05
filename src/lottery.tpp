//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_LOTTERY_TPP
#define LOTTERY_LOTTERY_TPP

#include <iostream>

#include "combinatorics.h"

template <uint8_t N> std::vector<std::vector<uint32_t>> computeTicketToGroupEdges(
        const std::vector<std::bitset<N>> &tickets,
        int t,
        const std::unordered_map<std::bitset<N>, uint32_t> &groupToId,
        uint32_t groupsPerTicket
) {
    std::vector<std::vector<uint32_t>> ticketToGroup(tickets.size(), std::vector<uint32_t>(groupsPerTicket));
    for (uint32_t i = 0; i < tickets.size(); ++i) {
        auto groupsInTicket = computeSubCombinations<N>(tickets[i], t);
        std::transform(
                groupsInTicket.begin(),
                groupsInTicket.end(),
                ticketToGroup[i].begin(),
                [groupToId](auto group){ return groupToId.at(group); }
        );
    }
    return ticketToGroup;
}

template <uint8_t N> std::vector<std::vector<uint32_t>> computeGroupToDrawEdges(
        const std::vector<std::bitset<N>> &groups,
        int p,
        int t,
        const std::unordered_map<std::bitset<N>, uint32_t> &drawToId,
        uint32_t drawsPerGroup
) {
    assert (p >= t);
    int extension = p - t;
    std::vector<std::vector<uint32_t>> groupToDraw(groups.size(), std::vector<uint32_t>(drawsPerGroup));
    for (uint32_t i = 0; i < groups.size(); ++i) {
        auto drawsWithGroup = computeSuperCombinations<N>(groups[i], extension);
        std::transform(
                drawsWithGroup.begin(),
                drawsWithGroup.end(),
                groupToDraw[i].begin(),
                [drawToId](auto draw) { return drawToId.at(draw); }
        );
    }
    return groupToDraw;
}


template <uint8_t N> bool verifyTCoverage(const std::vector<std::bitset<N>> &samples, const std::vector<std::bitset<N>> &cover, int t) {
    for (auto sampleIter = samples.begin(); sampleIter != samples.end(); ++sampleIter) {
        bool found = false;
        for (auto coverIter = cover.begin(); coverIter != cover.end(); ++coverIter) {
            auto intersection = *sampleIter & *coverIter;
            if (intersection.count() >= t) {
                found = true;
                break;
            }

        }
        if (!found) {
            return false;
        }
    }
    return true;
}

#endif //LOTTERY_LOTTERY_TPP
