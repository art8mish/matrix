#pragma once

#include "array.hpp"
#include <iostream>

namespace matrix {

template <typename T> class Matrix {
    size_t rows_ = 0;
    size_t cols_ = 0;
    Array<Array<T>> matrix_;

public:
    Matrix(std::initializer_list<std::initializer_list<T>> init)
        : rows_(init.size()),
          cols_(init.size() > 0 ? init.begin()->size() : 0),
          matrix_(rows_, Array<T>(cols_, init.begin(), init.end()))
    {
        for (const auto& row : init) {
            if (row.size() != cols_) {
                throw std::invalid_argument("Rows size should be equal");
            }
        }

        size_t idx = 0;
        for (const auto& row : init) {
            std::copy(row.begin(), row.end(), data_ + idx);
            idx += cols_;
        }
    }

    Matrix(size_t rows, size_t columns, const T &val)
        : rows_(rows), cols_(columns), matrix_(rows_, Array<T>(cols_, val)) {}
    Matrix(size_t n, const T &val): Matrix(n, n, val) {}

    Matrix(const Matrix<T> &rhs) = default;
    Matrix(Matrix<T> &&) = default;
    Matrix<T> &operator=(const Matrix<T> &) = default;
    Matrix<T> &operator=(Matrix<T> &&) = default;
    ~Matrix() = default;

    size_t rows() const {
        return rows_;
    }

    size_t columns() const {
        return cols_;
    }

    Array<T> &operator[](size_t row_index) {
        return matrix_[row_index];
    };

    const Array<T> &operator[](size_t row_index) const {
        return matrix_[row_index];
    };
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    // std::ios_base::fmtflags original_flags = os.flags();
    size_t rows = matrix.rows();
    size_t cols = matrix.columns();

    for (size_t row_i = 0; row_i < rows; ++row_i) {
        for (size_t col_j = 0; col_j < cols; ++col_j)
            os << matrix[row_i][col_j] << ' ';
        os << '\n';
    }
    // os.flags(original_flags);
    return os;
}

} // namespace matrix