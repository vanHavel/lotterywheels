
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <unordered_set>

#include "combinatorics.h"
#include "lottery.h"
#include "utils.h"

#define CONSTANT_N 27
#define CONSTANT_K 6
#define CONSTANT_P 4
#define CONSTANT_T 3
#define COVER_SIZE 100
#define INITIAL_TEMPERATURE 5
#define TEMPERATURE_DECAY 0.99
#define TEMPERATURES_WITHOUT_IMPROVEMENT 10
#define ITERATION_MULTIPLIER 20
#define NUMBER_OF_RUNS 10

int main() {
    static_assert(CONSTANT_N > 0 && CONSTANT_K > 0 && CONSTANT_T > 0 && CONSTANT_P > 0 && COVER_SIZE > 0);
    static_assert(CONSTANT_K <= CONSTANT_N && CONSTANT_P <= CONSTANT_N && CONSTANT_T <= CONSTANT_N);
    static_assert(CONSTANT_T <= CONSTANT_K && CONSTANT_T <= CONSTANT_P);

    const auto binomialCoefficients = computeBinomialCoefficients(CONSTANT_N);
    assert (COVER_SIZE <= binomialCoefficients[CONSTANT_N][CONSTANT_K]);

    std::cerr << "Computing combinations..." << std::endl;
    const auto allDraws = computeAllCombinations<CONSTANT_N>(CONSTANT_P);
    const auto allTickets = computeAllCombinations<CONSTANT_N>(CONSTANT_K);
    const auto allGroups = computeAllCombinations<CONSTANT_N>(CONSTANT_T);

    const auto drawToId = computeInverseMapping<CONSTANT_N>(allDraws);
    const auto ticketToId = computeInverseMapping<CONSTANT_N>(allTickets);
    const auto groupToId = computeInverseMapping<CONSTANT_N>(allGroups);

    std::cerr << "Computing ticket to group relation..." << std::endl;
    const auto ticketToGroup = computeTicketToGroupEdges<CONSTANT_N>(allTickets, CONSTANT_T, groupToId);
    std::cerr << "Computing group to draw relation..." << std::endl;
    const auto groupToDraw = computeGroupToDrawEdges<CONSTANT_N>(allGroups, CONSTANT_P, CONSTANT_T, drawToId);

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<uint32_t> ticketDistribution(0, (uint32_t) allTickets.size() - 1);
    std::uniform_int_distribution<uint32_t> coverDistribution(0, COVER_SIZE - 1);
    std::uniform_int_distribution<uint8_t> ticketMemberDistribution(0, CONSTANT_K - 1);
    std::uniform_int_distribution<uint8_t> universeDistribution(0, CONSTANT_N - 1);
    std::uniform_real_distribution<double> uniformDistribution(0, 1);


    uint32_t bestUncovered = 1000000000;
    std::vector<uint32_t> bestCover;
    for (int run = 0; run < NUMBER_OF_RUNS; ++run) {
        std::cerr << "Run number " << run << "..." << std::endl;
        std::cerr << "Computing initial cover..." << std::endl;
        std::unordered_set<uint32_t> initialCoverSet;
        while (initialCoverSet.size() < COVER_SIZE) {
            uint32_t ticketID = ticketDistribution(generator);
            initialCoverSet.insert(ticketID);
        }
        std::vector<uint32_t> currentCover(initialCoverSet.begin(), initialCoverSet.end());
        std::vector<uint32_t> coverage(allDraws.size());
        uint32_t covered = computeDrawCoverage(currentCover, ticketToGroup, groupToDraw, coverage);
        uint32_t uncovered = ((uint32_t) allDraws.size()) - covered;

        std::cerr << "Initial cost is " << uncovered << std::endl;
        std::cerr << "Starting simulated annealing..." << std::endl;
        double temperature = INITIAL_TEMPERATURE;
        uint32_t iterationsPerTemperature = ITERATION_MULTIPLIER * COVER_SIZE * CONSTANT_K * (CONSTANT_N - CONSTANT_K);
        int temperaturesWithoutImprovement = 0;
        do {
            uint32_t uncoveredBefore = uncovered;
            int badMoves = 0, badMovesAccepted = 0;
            for (int i = 0; i < iterationsPerTemperature; ++i) {
                uint32_t oldCost = uncovered;
                uint32_t pickedTicketIndex = coverDistribution(generator);
                uint32_t pickedMemberIndex = ticketMemberDistribution(generator);
                uint32_t pickedTicketID = currentCover[pickedTicketIndex];

                auto pickedTicketSet = allTickets[pickedTicketID];
                auto reducedTicketSet = removeIthMember<CONSTANT_N>(pickedTicketSet, pickedMemberIndex);
                //TODO this could add the same member removed before
                auto newTicketSet = addRandomMember<CONSTANT_N>(reducedTicketSet, universeDistribution, generator);
                uint32_t newTicketID = ticketToId.at(newTicketSet);

                uncovered += removeTicketFromCover(coverage, pickedTicketID, ticketToGroup, groupToDraw);
                uncovered -= addTicketToCover(coverage, newTicketID, ticketToGroup, groupToDraw);
                currentCover[pickedTicketIndex] = newTicketID;

                assert (uncovered >= 0);
                if (uncovered == 0) { break; }
                else if (uncovered > oldCost) {
                    badMoves++;
                    uint32_t delta = uncovered - oldCost;
                    double probability = exp(-((double) delta) / temperature);
                    double probe = uniformDistribution(generator);
                    if (probe > probability) {
                        // undo move
                        uncovered += removeTicketFromCover(coverage, newTicketID, ticketToGroup, groupToDraw);
                        uncovered -= addTicketToCover(coverage, pickedTicketID, ticketToGroup, groupToDraw);
                        currentCover[pickedTicketIndex] = pickedTicketID;
                    } else {
                        badMovesAccepted++;
                    }
                }
            }
            double badMoveAcceptanceRatio = ((double) badMovesAccepted) / ((double) badMoves);
            double badMovesRatio = ((double) badMoves) / ((double) iterationsPerTemperature);
            std::cerr << "Temperature: " << temperature <<
                      ", Cost: " << uncovered <<
                      ", Bad Moves Acceptance: " << badMoveAcceptanceRatio <<
                      std::endl;
            temperature *= TEMPERATURE_DECAY;
            temperaturesWithoutImprovement = (uncovered >= uncoveredBefore ? temperaturesWithoutImprovement + 1 : 0);
        } while (uncovered > 0 && temperaturesWithoutImprovement <= TEMPERATURES_WITHOUT_IMPROVEMENT);
        if (uncovered < bestUncovered) {
            bestCover = currentCover;
            bestUncovered = uncovered;
        }
        if (bestUncovered == 0) {
            break;
        }
    }

    std::vector<std::bitset<CONSTANT_N>> coverTickets;
    std::transform(
            bestCover.begin(),
            bestCover.end(),
            std::back_inserter(coverTickets),
            [allTickets](auto i){ return allTickets[i]; }
    );
    for (int i = 0; i < COVER_SIZE; ++i) {
        for (uint8_t j = 0; j < CONSTANT_N; ++j) {
            if (coverTickets[i].test(j)) {
                std::cout << (j + 1) << " ";
            }
        }
        std::cout << std::endl;
    }
    if (bestUncovered == 0) {
        assert (verifyTCoverage<CONSTANT_N>(allDraws, coverTickets, CONSTANT_T));
        std::cout << "Valid cover";
    }
    else {
        std::cout << "Invalid cover with cost " << bestUncovered;
    }

}