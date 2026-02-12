#pragma once

#include "array.hpp"
#include "utils.hpp"
#include <cassert>
#include <concepts> // requires
#include <iostream>
#include <type_traits>

namespace matrix {

template <typename T>
    requires std::is_arithmetic_v<T>
class Matrix {
    size_t rows_ = 0;
    size_t cols_ = 0;
    Array<Array<T>> matrix_;

    bool is_zero(const T val, const T eps = epsilon<T>()) const {
        if constexpr (std::is_floating_point_v<T>)
            return std::abs(val) < eps;
        else if constexpr (std::is_integral_v<T>)
            return val == 0;
    }

    bool is_upper_triangular_() const {
        for (size_t row = 1; row < rows_; ++row)
            for (size_t col = 0; col < row; ++col)
                if (!is_zero(matrix_[row][col]))
                    return false;
        return true;
    }

    bool is_lower_triangular_() const {
        for (size_t row = 0; row < rows_ - 1; ++row)
            for (size_t col = row + 1; col < cols_; ++col)
                if (!is_zero(matrix_[row][col]))
                    return false;
        return true;
    }

    // static size_t max_column_element_index_(Array<Array<T>> &matrix, size_t column) {
    //     assert(column < matrix.size() && column < matrix[0]);

    //     size_t max_val_row = column;
    //     for (size_t row = column + 1; row < rows_; ++row) {
    //         if (std::abs(matrix[row][column]) > std::abs(matrix[max_col_val_i][column]))
    //             max_col_val_i = row;
    //     }
    //     return max_val_row
    // }

    T floating_determinant() const {
        assert(rows_ == cols_ && rows_ > 1);
        static_assert(std::is_floating_point_v<T>, "Floating determinant requieres floating type");

        const T eps = epsilon<T>();
        Array<Array<T>> matrix = matrix_;

        T det = 1;
        for (size_t col = 0; col < cols_; ++col) {
            size_t max_val_row = col;
            for (size_t row = col + 1; row < rows_; ++row) {
                if (std::abs(matrix[row][col]) > std::abs(matrix[max_val_row][col]))
                    max_val_row = row;
            }

            if (is_zero(matrix[max_val_row][col], eps))
                return 0;

            if (max_val_row != col) {
                std::swap(matrix[col], matrix[max_val_row]);
                det *= -1;
            }

            det *= matrix[col][col];

            for (size_t row = col + 1; row < rows_; ++row) {
                if (is_zero(matrix[row][col], eps))
                    continue;

                double coef = matrix[row][col] / matrix[col][col];
                for (size_t k = 0; k < cols_; ++k)
                    matrix[row][k] -= coef * matrix[col][k];
            }
        }

        return det;
    }

    T integral_determinant() const {
        assert(rows_ == cols_ && rows_ > 1);
        static_assert(std::is_integral_v<T>, "Integral determinant requieres integral type");

        Array<Array<T>> matrix = matrix_;
        T sign = 1;
        T minor_k_prev = 1;
        for (size_t k = 0; k < cols_ - 1; ++k) {

            size_t max_val_row = k;
            for (size_t row = k + 1; row < rows_; ++row) {
                if (std::abs(matrix[row][k]) > std::abs(matrix[max_val_row][k]))
                    max_val_row = row;
            }

            if (matrix[max_val_row][k] == 0)
                return 0;

            if (max_val_row != k) {
                std::swap(matrix[k], matrix[max_val_row]);
                sign *= -1;
            }

            for (size_t row = k + 1; row < rows_; ++row) {
                for (size_t col = k + 1; col < cols_; ++col) {
                    T minor_k = matrix[k][k] * matrix[row][col] - matrix[row][k] * matrix[k][col];
                    matrix[row][col] = minor_k / minor_k_prev;
                }
            }
            minor_k_prev = matrix[k][k];
        }
        return sign * matrix[rows_ - 1][cols_ - 1];
    }

    T sarrus_determinant() const {
        assert(rows_ == cols_ && rows_ == 3);

        auto &m = matrix_;
        return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
               m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0] -
               m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
    }

public:
    Matrix(std::initializer_list<std::initializer_list<T>> init)
        : rows_(init.size()), cols_(init.size() > 0 ? init.begin()->size() : 0),
          matrix_(init.begin(), init.end()) {
        for (const auto &row : init)
            if (row.size() != cols_)
                throw std::invalid_argument("Rows size should be equal");
    }

    Matrix(size_t rows, size_t columns, const T &val)
        : rows_(rows), cols_(columns), matrix_(rows_, Array<T>(cols_, val)) {}
    Matrix(size_t n, const T &val) : Matrix(n, n, val) {}

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

    bool is_triangular() const {
        if (rows_ < 2 || cols_ < 2)
            return true;
        return is_upper_triangular_() || is_lower_triangular_();
    }

    T determinant() const {
        if (rows_ != cols_)
            throw std::runtime_error("Can't calculate determinant for non quadratic matrix");

        if (rows_ == 1)
            return matrix_[0][0];

        if (rows_ == 2)
            return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

        if (rows_ == 3)
            return sarrus_determinant();

        // if (is_triangular()) {
        //     T det = 1;
        //     for (size_t i = 0; i < rows_; ++i)
        //         det *= matrix_[i][i];
        //     return det;
        // }

        if constexpr (std::is_floating_point_v<T>)
            return floating_determinant();
        else if constexpr (std::is_integral_v<T>)
            return integral_determinant();
        throw std::runtime_error("Incompatible type");
    }
};

template <typename T> std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
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