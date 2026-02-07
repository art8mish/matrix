

#include "array.hpp"

template <typename T> 
Array<T> operator +(const Array<T> &lhs, const Array<T> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::logic_error("Array size is incompatible");
    }
    Array<T> tmp = lhs;
    tmp += rhs;
    return tmp;
};