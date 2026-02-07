

#include "array.hpp"

namespace matrix {

template <typename T> class Matrix {
    size_t rows_ = 0;
    size_t cols_ = 0;
    Array<Array<T>> matrix_;

public:
    Matrix(size_t rows, size_t columns, const T &val)
        : rows_(rows), cols_(columns), matrix_(rows, Array<T>{columns, val}) {}
    Matrix(size_t n, const T &val): Matrix(n, n, val) {}

    Matrix(const Matrix<T> &rhs) = default;
    Matrix(Matrix<T> &&) = default;
    Matrix<T> &operator=(const Matrix<T> &) = default;
    Matrix<T> &operator=(Matrix<T> &&) = default;
    ~Matrix() = default;

    Array<T> &operator[](size_t row_index) {
        return matrix_[row_index];
    };

    const Array<T> &operator[](size_t row_index) const {
        return matrix_[row_index];
    };


};
} // namespace matrix