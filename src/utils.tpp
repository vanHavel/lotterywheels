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

#endif //LOTTERY_COMBINATORICS_TPP
