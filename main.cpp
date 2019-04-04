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
    auto combs3 = computeAllCombinations<5>(3);
    auto combs2 = {
            std::bitset<5>("11000"), std::bitset<5>("00011")
    };
    std::cout << verifyTCoverage<5>(combs3, combs2, 2);
}