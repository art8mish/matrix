#pragma once

#include <utility>
#include <stdexcept>
#include <iterator>
#include <cassert>
#include <initializer_list>

#include <buffer.hpp>

namespace matrix {

template <typename T>
class Array : private Buffer<T> {
    using Buffer<T>::buffer_;
    using Buffer<T>::size_;
    using Buffer<T>::used_;
    using Buffer<T>::construct;


public:

    Array(const Array<T> &rhs) : Buffer<T>(rhs.used_) {
        while (used_ != size_) {
            construct(buffer_ + used_, rhs.buffer_[used_]);
            ++used_;
        }
    }
    Array(Array<T> &&rhs) = default;
    Array<T> &operator=(const Array<T> &rhs) {
        if (this == &rhs)
            return *this;
        Array tmp{rhs};
        std::swap(*this, tmp);
        return *this;
    }
    Array<T> &operator=(Array<T> &&rhs) = default;


private:
    template <typename It> 
    Array(size_t size, It begin, It end) : Buffer<T>(size) {
        assert(size == static_cast<size_t>(std::distance(begin, end)));

        for (It it = begin; it != end; ++it) {
            construct(buffer_ + used_, *it);
            ++used_;
        }
    }

public:
    Array(std::initializer_list<T> init) 
        : Array(init.size(), init.begin(), init.end()) {}

    template <typename It> Array(It begin, It end) 
        : Array(static_cast<size_t>(std::distance(begin, end)), begin, end) {}

    Array(size_t size, const T& val) : Buffer<T>(size) {
        while (used_ != size_) {
            construct(buffer_ + used_, val);
            ++used_;
        }
    }

    T &operator [](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Array index out of range");
        }
        return buffer_[index];
    }

    const T &operator [](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Array index out of range");
        }
        return buffer_[index];
    }

    size_t size() const {
        return size_;
    }

    bool operator ==(const Array<T> &rhs) {
        if (size_ != rhs.size_) {
            throw std::invalid_argument("Array size is incompatible");
        }

        bool eq_flg = true; 
        for (size_t i = 0; i < size_; ++i) {
            if (buffer_[i] != rhs.buffer_[i]) {
                eq_flg = false;
                break;
            }
        }
        return eq_flg;
    }

    bool operator !=(const Array<T> &rhs) {
        return !(*this == rhs);
    }


    Array<T> &operator +=(const Array<T> &rhs) {
        if (size_ != rhs.size_) {
            throw std::invalid_argument("Array size is incompatible");
        }

        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] += rhs.buffer_[i];
        }
        return *this;
    }

    Array<T> &operator +=(const T &val) {
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] += val;
        }
        return *this;
    }

    Array<T> &operator -=(const Array<T> &rhs) {
        if (size_ != rhs.size_) {
            throw std::invalid_argument("Array size is incompatible");
        }

        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] -= rhs.buffer_[i];
        }
        return *this;
    }

    Array<T> &operator -=(const T &val) {
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] -= val;
        }
        return *this;
    }

    Array<T> &operator *=(const T &val) {
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] *= val;
        }
        return *this;
    }

    // Array<T> &operator /=(const T &val) {
    //     for (size_t i = 0; i < size_; ++i) {
    //         buffer_[i] /= val;
    //     }
    //     return *this;
    // }
};


template <typename T> 
Array<T> operator +(const Array<T> &lhs, const Array<T> &rhs) {
    Array<T> tmp = lhs;
    tmp += rhs;
    return tmp;
};

template <typename T> 
Array<T> operator +(const Array<T> &arr, const T &val) {
    Array<T> tmp = arr;
    tmp += val;
    return tmp;
};

template <typename T> 
Array<T> operator +(const T &val, const Array<T> &arr) {
    return arr + val;
};


template <typename T> 
Array<T> operator -(const Array<T> &lhs, const Array<T> &rhs) {
    Array<T> tmp = lhs;
    tmp -= rhs;
    return tmp;
};

template <typename T> 
Array<T> operator -(const Array<T> &arr, const T &val) {
    Array<T> tmp = arr;
    tmp -= val;
    return tmp;
};

template <typename T> 
Array<T> operator *(const Array<T> &arr, const T &val) {
    Array<T> tmp = arr;
    tmp *= val;
    return tmp;
};

template <typename T> 
Array<T> operator *(const T &val, const Array<T> &arr) {
    return arr * val;
};

// template <typename T> 
// Array<T> operator /(const Array<T> &arr, const T &val) {
//     Array<T> tmp = arr;
//     tmp /= val;
//     return tmp;
// };




} // namespace matrix