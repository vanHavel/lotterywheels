//
// Created by Lukas Huwald on 2019-04-05.
//

#include "lottery.h"

std::vector<uint32_t> computeDrawCoverage(
        const std::vector<uint32_t> &cover,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw,
        uint32_t numberOfDraws
) {
    std::vector<uint32_t> coverage(numberOfDraws, 0);
    for (uint32_t coverIter : cover) {
        for (uint32_t groupIter : ticketToGroup[coverIter]) {
            for (uint32_t drawIter : groupToDraw[groupIter]) {
                coverage[drawIter]++;
            }
        }
    }
    return coverage;
}

uint32_t computeUncoveredDrawCount(std::vector<uint32_t> coverage) {
    uint32_t uncovered = 0;
    for (uint32_t coverCount : coverage) {
        if (coverCount == 0) { uncovered++; }
    }
    return uncovered;
}