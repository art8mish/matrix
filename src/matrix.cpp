
#include "matrix.hpp"

int main() {
    matrix::Matrix<double> A {2, 3, 0};
    matrix::Matrix<double> B {3, 2, 0};
    A = B;
}