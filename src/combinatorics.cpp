//
// Created by Lukas Huwald on 2019-04-04.
//

#include "combinatorics.h"

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