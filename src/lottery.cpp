//
// Created by Lukas Huwald on 2019-04-05.
//

#include "lottery.h"

uint32_t computeDrawCoverage(
        const std::vector<uint32_t> &cover,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw,
        std::vector<uint32_t> &coverage
) {
    uint32_t covered = 0;
    for (uint32_t coverTicket : cover) {
        covered += addTicketToCover(coverage, coverTicket, ticketToGroup, groupToDraw);
    }
    return covered;
}

uint32_t removeTicketFromCover(
        std::vector<uint32_t> &coverage,
        uint32_t ticketID,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw
) {
    uint32_t removed = 0;
    for (uint32_t group : ticketToGroup[ticketID]) {
        for (uint32_t draw : groupToDraw[group]) {
            coverage[draw]--;
            if (coverage[draw] == 0) {
                removed++;
            }
        }
    }
    return removed;
}

uint32_t addTicketToCover(
        std::vector<uint32_t> &coverage,
        uint32_t ticketID,
        const std::vector<std::vector<uint32_t>> &ticketToGroup,
        const std::vector<std::vector<uint32_t>> &groupToDraw
) {
    uint32_t added = 0;
    for (uint32_t group : ticketToGroup[ticketID]) {
        for (uint32_t draw : groupToDraw[group]) {
            if (coverage[draw] == 0) {
                added++;
            }
            coverage[draw]++;
        }
    }
    return added;
}