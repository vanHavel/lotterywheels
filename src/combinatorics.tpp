//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_COMBINATORICS_TPP
#define LOTTERY_COMBINATORICS_TPP

template <int N> std::vector<std::bitset<N>> computeAllCombinations(int k, int from) {
    if (k == 0) { return {std::bitset<N>()}; }
    std::vector<std::bitset<N>> combinations;
    for (int i = from; i < N - k + 1; ++i) {
        auto subCombinations = computeAllCombinations<N>(k - 1, i + 1);
        std::transform(
                subCombinations.begin(),
                subCombinations.end(),
                std::back_inserter(combinations),
                [i](auto set) { set[i] = true; return set; }
        );
    }
    return combinations;
}

template <int N> std::vector<std::bitset<N>> computeAllCombinations(int k) {
    return computeAllCombinations<N>(k, 0);
}

#endif //LOTTERY_COMBINATORICS_TPP
