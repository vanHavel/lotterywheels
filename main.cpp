
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "combinatorics.h"

template <int N> std::unordered_map<std::bitset<N>, uint32_t> computeInverseMapping(std::vector<std::bitset<N>> vec) {
    std::unordered_map<std::bitset<N>, uint32_t> res;
    for (uint32_t i = 0; i < vec.size(); ++i) {
        res[vec[i]] = i;
    }
    return res;
}

template <int N> bool verifyTCoverage(std::vector<std::bitset<N>> samples, std::vector<std::bitset<N>> cover, int t) {
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

int main() {
    auto combs = computeSuperCombinations<5>(std::bitset<5>("00000"), 3);
    for(auto i = combs.begin(); i != combs.end(); ++i) {
        std::cout << *i << "\n";
    }

}