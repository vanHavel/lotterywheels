
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <unordered_set>

#include "combinatorics.h"
#include "lottery.h"
#include "utils.h"

#define CONSTANT_N 5
#define CONSTANT_K 3
#define CONSTANT_P 3
#define CONSTANT_T 2
#define COVER_SIZE 1
#define INITIAL_TEMPERATURE 1.0
#define TEMPERATURE_DECAY 0.99
#define ITERATIONS_PER_TEMPERATURE 100



int main() {
    static_assert(CONSTANT_N > 0 && CONSTANT_K > 0 && CONSTANT_T > 0 && CONSTANT_P > 0 && COVER_SIZE > 0);
    static_assert(CONSTANT_K <= CONSTANT_N && CONSTANT_P <= CONSTANT_N && CONSTANT_T <= CONSTANT_N);
    static_assert(CONSTANT_T <= CONSTANT_K && CONSTANT_T <= CONSTANT_P);

    const auto binomialCoefficients = computeBinomialCoefficients(CONSTANT_N);
    assert (COVER_SIZE <= binomialCoefficients[CONSTANT_N][CONSTANT_K]);

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
    std::uniform_int_distribution<uint32_t> coverDistribution(0, COVER_SIZE - 1);
    std::uniform_int_distribution<uint32_t> ticketMemberDistribution(0, CONSTANT_K - 1);
    std::uniform_int_distribution<uint32_t> universeDistribution(0, CONSTANT_N - 1);
    std::uniform_real_distribution<double> uniformDistribution(0, 1);

    std::unordered_set<uint32_t> initialCoverSet;
    while (initialCoverSet.size() < COVER_SIZE) {
        uint32_t ticketID = ticketDistribution(generator);
        initialCoverSet.insert(ticketID);
    }
    std::vector<uint32_t> currentCover(initialCoverSet.begin(), initialCoverSet.end());
    std::vector<uint32_t> coverage = computeDrawCoverage(currentCover, ticketToGroup, groupToDraw, (uint32_t) allDraws.size());
    uint32_t uncovered = computeUncoveredDrawCount(coverage);

    bool done = false;
    double temperature = INITIAL_TEMPERATURE;
    while (!done) {
        for (int i = 0; i < ITERATIONS_PER_TEMPERATURE; ++i) {
            uint32_t oldCost = uncovered;
            uint32_t pickedTicketIndex = coverDistribution(generator);
            uint32_t pickedMemberIndex = ticketMemberDistribution(generator);
            uint32_t pickedTicketID = currentCover[pickedTicketIndex];

            auto pickedTicketSet = allTickets[pickedTicketID];
            auto reducedTicketSet = removeIthMember<CONSTANT_N>(pickedTicketSet, pickedMemberIndex);
            auto newTicketSet = addRandomMember<CONSTANT_N>(reducedTicketSet, universeDistribution, generator);
            uint32_t newTicketID = ticketToId.at(newTicketSet);

            uncovered += removeTicketFromCover(coverage, pickedTicketID, ticketToGroup, groupToDraw);
            uncovered -= addTicketToCover(coverage, newTicketID, ticketToGroup, groupToDraw);
            currentCover[pickedTicketIndex] = newTicketID;

            assert (uncovered >= 0);
            if (uncovered == 0) {
                break;
            }
            else if (uncovered > oldCost) {
                uint32_t delta = uncovered - oldCost;
                double probability = exp(-((double) delta) / temperature);
                double probe = uniformDistribution(generator);
                if (probe > probability) {
                    // undo move
                    uncovered += removeTicketFromCover(coverage, newTicketID, ticketToGroup, groupToDraw);
                    uncovered -= addTicketToCover(coverage, pickedTicketID, ticketToGroup, groupToDraw);
                    currentCover[pickedTicketIndex] = pickedTicketID;
                }
            }
        }
        temperature *= TEMPERATURE_DECAY;
        done = true;
    }

}