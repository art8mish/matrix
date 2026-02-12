#include <ctime>
#include <iostream>

#include "matrix.hpp"

int main() {
    try {
        size_t size = 0;
        std::cin >> size;
        if (!std::cin.good())
            throw std::invalid_argument("Incorrect size");

        matrix::Matrix<long> matrix{size, 0};
        long val = 0;
        for (size_t row = 0; row < size; ++row) {
            for (size_t col = 0; col < size; ++col) {
                std::cin >> val;
                if (!std::cin.good())
                    throw std::invalid_argument("Incorrect matrix value");
                matrix[row][col] = val;
            }
        }

#ifndef NDEBUG
        auto start_time = std::clock();
#endif
        long det = matrix.determinant();
#ifndef NDEBUG
        auto duration = std::clock() - start_time;
#endif
        std::cout << det << std::endl;
#ifndef NDEBUG
        std::cout << "\nRuntime: " << duration << " us" << std::endl;
#endif
        return 0;
    } catch (const std::invalid_argument &e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (const std::out_of_range &e) {
        std::cout << "Matrix is out of range: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 3;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
        return 4;
    }
}
