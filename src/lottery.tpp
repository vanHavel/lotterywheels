//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_LOTTERY_TPP
#define LOTTERY_LOTTERY_TPP

#include "combinatorics.h"

template <uint32_t N> std::vector<std::vector<uint32_t>> computeTicketToGroupEdges(
        const std::vector<std::bitset<N>> &tickets,
        int t,
        const std::unordered_map<std::bitset<N>, uint32_t> &groupToId
) {
    //TODO the size of the subvectors is actually known by a binomial coefficient
    std::vector<std::vector<uint32_t>> ticketToGroup(tickets.size());
    for (uint32_t i = 0; i < tickets.size(); ++i) {
        auto groupsInTicket = computeSubCombinations<N>(tickets[i], t);
        std::transform(
                groupsInTicket.begin(),
                groupsInTicket.end(),
                std::back_inserter(ticketToGroup[i]),
                [groupToId](auto group){ return groupToId.at(group); }
        );
    }
    return ticketToGroup;
}

template <uint32_t N> std::vector<std::vector<uint32_t>> computeGroupToDrawEdges(
        const std::vector<std::bitset<N>> &groups,
        int p,
        int t,
        const std::unordered_map<std::bitset<N>, uint32_t> &drawToId
) {
    assert (p >= t);
    int extension = p - t;
    //TODO size of subvectors is actually known by binomial coefficients
    std::vector<std::vector<uint32_t>> groupToDraw(groups.size());
    for (uint32_t i = 0; i < groups.size(); ++i) {
        auto drawsWithGroup = computeSuperCombinations<N>(groups[i], extension);
        std::transform(
                drawsWithGroup.begin(),
                drawsWithGroup.end(),
                std::back_inserter(groupToDraw[i]),
                [drawToId](auto draw) { return drawToId.at(draw); }
        );
    }
    return groupToDraw;
}


template <uint32_t N> bool verifyTCoverage(std::vector<std::bitset<N>> samples, std::vector<std::bitset<N>> cover, int t) {
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
