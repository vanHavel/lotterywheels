//
// Created by Lukas Huwald on 2019-04-04.
//

#ifndef LOTTERY_UTILS_TPP
#define LOTTERY_UTILS_TPP

template <uint8_t N> std::unordered_map<std::bitset<N>, uint32_t> computeInverseMapping(std::vector<std::bitset<N>> vec) {
    std::unordered_map<std::bitset<N>, uint32_t> res;
    for (uint32_t i = 0; i < vec.size(); ++i) {
        res[vec[i]] = i;
    }
    return res;
}

template <uint8_t N> std::bitset<N> removeIthMember(const std::bitset<N> bitset, int index) {
    int seen = 0;
    uint8_t i;
    for (i = 0; i < N; ++i) {
       if (bitset[i]) {
           if (seen == index) {
               break;
           }
           else {
               seen++;
           }
       }
    }
    assert (i < N);
    auto res = bitset;
    res.reset(i);
    return res;
}

template <uint8_t N> std::bitset<N> addRandomMember(
        const std::bitset<N> bitset,
        std::uniform_int_distribution<uint8_t> universeDistribution,
        std::mt19937 &generator
) {
    uint8_t newBit;
    do {
        newBit = universeDistribution(generator);
    } while (bitset.test(newBit));
    auto res = bitset;
    res.set(newBit);
    return res;
}

#endif //LOTTERY_COMBINATORICS_TPP
