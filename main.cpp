#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <unordered_map>


std::vector<std::vector<int32_t>> computeBinomialCoefficients(int n) {
    std::vector<std::vector<int32_t>> coefficients((std::size_t) n+1, std::vector<int32_t>((std::size_t) n+1, 0));
    for (int i = 0; i <= n; ++i) {
        coefficients[i][0] = 1;
        coefficients[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            coefficients[i][j] = coefficients[i-1][j] + coefficients[i-1][j-1];
        }
    }
    return coefficients;
}

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

template <int N> std::unordered_map<std::bitset<N>, uint32_t> computeInverseMapping(std::vector<std::bitset<N>> vec) {
    std::unordered_map<std::bitset<N>, uint32_t> res;
    for (uint32_t i = 0; i < vec.size(); ++i) {
        res[vec[i]] = i;
    }
    return res;
}

int main() {
    auto combs = computeAllCombinations<5>(3, 0);
    auto inv = computeInverseMapping<5>(combs);
    for (auto iter = inv.begin(); iter != inv.end(); ++iter) {
        std::cout << iter->first << " -> " << iter->second << "\n";
    }
}