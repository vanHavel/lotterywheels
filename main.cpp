
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <unordered_set>

#include "combinatorics.h"
#include "lottery.h"

#define CONSTANT_N 5
#define CONSTANT_K 3
#define CONSTANT_P 3
#define CONSTANT_T 2
#define CONSTANT_C 100

template <uint32_t N> std::unordered_map<std::bitset<N>, uint32_t> computeInverseMapping(std::vector<std::bitset<N>> vec) {
    std::unordered_map<std::bitset<N>, uint32_t> res;
    for (uint32_t i = 0; i < vec.size(); ++i) {
        res[vec[i]] = i;
    }
    return res;
}

int main() {
    static_assert(CONSTANT_N > 0 && CONSTANT_K > 0 && CONSTANT_T > 0 && CONSTANT_P > 0 && CONSTANT_C > 0);
    static_assert(CONSTANT_K <= CONSTANT_N && CONSTANT_P <= CONSTANT_N && CONSTANT_T <= CONSTANT_N);
    static_assert(CONSTANT_T <= CONSTANT_K && CONSTANT_T <= CONSTANT_P);

    const auto binomialCoefficients = computeBinomialCoefficients(CONSTANT_N);
    assert (CONSTANT_C <= binomialCoefficients[CONSTANT_N][CONSTANT_K]);

    const auto allDraws = computeAllCombinations<CONSTANT_N>(CONSTANT_P);
    const auto allTickets = computeAllCombinations<CONSTANT_N>(CONSTANT_K);
    const auto allGroups = computeAllCombinations<CONSTANT_N>(CONSTANT_T);

    const auto drawToId = computeInverseMapping<CONSTANT_N>(allDraws);
    const auto ticketToId = computeInverseMapping<CONSTANT_N>(allTickets);
    const auto groupToId = computeInverseMapping<CONSTANT_N>(allGroups);

    const auto ticketToGroup = computeTicketToGroupEdges<CONSTANT_N>(allTickets, CONSTANT_T, groupToId);
    const auto groupToDraw = computeGroupToDrawEdges<CONSTANT_N>(allGroups, CONSTANT_P, CONSTANT_T, drawToId);

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<uint32_t> ticketDistribution(0, (uint32_t) allTickets.size() - 1);
    std::uniform_int_distribution<uint32_t> coverDistribution(0, CONSTANT_C - 1);
    std::uniform_int_distribution<uint32_t> ticketMemberDistribution(0, CONSTANT_K - 1);

    std::unordered_set<uint32_t> initialCoverSet;
    while (initialCoverSet.size() < CONSTANT_C) {
        uint32_t ticketID = ticketDistribution(generator);
        initialCoverSet.insert(ticketID);
    }
    std::vector<uint32_t> initialCover(initialCoverSet.begin(), initialCoverSet.end());


}