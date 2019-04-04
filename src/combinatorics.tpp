//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_COMBINATORICS_TPP
#define LOTTERY_COMBINATORICS_TPP

template <int N> std::vector<std::bitset<N>> computeSubCombinations(std::bitset<N> set, int k, int from) {
    if (k == 0) { return {std::bitset<N>()}; }
    std::vector<std::bitset<N>> combinations;
    for (int i = from; i < N - k + 1; ++i) {
        if (!set.test((std::size_t) i)) { continue; }
        auto subCombinations = computeSubCombinations<N>(set, k - 1, i + 1);
        std::transform(
                subCombinations.begin(),
                subCombinations.end(),
                std::back_inserter(combinations),
                [i](auto subSet) { subSet[i] = true; return subSet; }
        );
    }
    return combinations;
}

template <int N> std::vector<std::bitset<N>> computeSubCombinations(std::bitset<N> set, int k) {
    return computeSubCombinations<N>(set, k, 0);
}

template <int N> std::vector<std::bitset<N>> computeAllCombinations(int k) {
    return computeSubCombinations<N>(std::bitset<N>().flip(), k);
}

#endif //LOTTERY_COMBINATORICS_TPP
