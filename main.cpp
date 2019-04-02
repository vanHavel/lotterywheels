#include <bitset>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

std::vector<std::vector<int32_t>> computeBinomialCoefficients(std::size_t n) {
    std::vector<std::vector<int32_t>> coefficients(n+1, std::vector<int32_t>(n+1, 0));
    for (int i = 0; i <= n; ++i) {
        coefficients[i][0] = 1;
        coefficients[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            coefficients[i][j] = coefficients[i-1][j] + coefficients[i-1][j-1];
        }
    }
    return coefficients;
}

template <std::size_t N> std::vector<std::bitset<N>> computeAllCombinations(std::size_t k) {
    return computeAllCombinations<N>(k, 0);
}

template <std::size_t N> std::vector<std::bitset<N>> computeAllCombinations(std::size_t k, int from) {
    std::vector<std::bitset<N>> combinations;
    for (int i = from; i < N; ++i) {
        auto subCombinations = computeAllCombinations<N>(k - 1, from + 1);
        std::transform(
                subCombinations.begin(),
                subCombinations.end(),
                combinations.end(),
                [i](auto set) { set[i] = true; return set; }
        );
    }
    return combinations;
}