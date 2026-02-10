
#include "matrix.hpp"
#include <iostream>

int main() {
    const matrix::Matrix<double> A {2, 3, 1};
    std::cout << A;

    const matrix::Matrix<double> B = A;
    std::cout << B;
}

