//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_COMBINATORICS_TPP
#define LOTTERY_COMBINATORICS_TPP

template <uint8_t N> std::vector<std::bitset<N>> computeSubCombinations(const std::vector<uint8_t> &setBits, int k, int from) {
    if (k == 0) { return {std::bitset<N>()}; }
    std::vector<std::bitset<N>> combinations;
    for (int i = from; i < setBits.size() - k + 1; ++i) {
        auto subCombinations = computeSubCombinations<N>(setBits, k - 1, i + 1);
        uint8_t bit = setBits[i];
        std::transform(
                subCombinations.begin(),
                subCombinations.end(),
                std::back_inserter(combinations),
                [bit](auto subSet) { subSet[bit] = true; return subSet; }
        );
    }
    return combinations;
}

template <uint8_t N> std::vector<std::bitset<N>> computeSubCombinations(const std::bitset<N> &set, int k) {
    std::vector<uint8_t> setBits;
    for (uint8_t i = 0; i < N; ++i) {
        if (set[i]) { setBits.push_back(i); }
    }
    return computeSubCombinations<N>(setBits, k, 0);
}

template <uint8_t N> std::vector<std::bitset<N>> computeAllCombinations(int k) {
    return computeSubCombinations<N>(std::bitset<N>().flip(), k);
}

template <uint8_t N> std::vector<std::bitset<N>> computeSuperCombinations(const std::bitset<N> &set, int k) {
    std::vector<uint8_t> unsetBits;
    for (uint8_t i = 0; i < N; ++i) {
        if (!set[i]) { unsetBits.push_back(i); }
    }
    assert(unsetBits.size() >= k);
    auto extensions = computeSubCombinations<N>(unsetBits, k, 0);

    std::vector<std::bitset<N>> combinations;
    std::transform(
            extensions.begin(),
            extensions.end(),
            std::back_inserter(combinations),
            [set](auto extension) {return set | extension; }
    );

    return combinations;

}

#endif //LOTTERY_COMBINATORICS_TPP
