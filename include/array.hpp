#pragma once

#include <utility>
#include <stdexcept>

#include <buffer.hpp>

namespace matrix {

template <typename T>
class Array : private Buffer<T> {
    using Buffer<T>::buffer_;
    using Buffer<T>::size_;
    using Buffer<T>::used_;
    using Buffer<T>::construct;

public:
    Array(size_t size, const T& val) : Buffer<T>(size) {
        while (used_ != size_) {
            construct(buffer_ + used_, val);
            ++used_;
        }
    }
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


    Array<T> &operator +=(const Array<T> &rhs) {
        if (size_ != rhs.size_) {
            throw std::logic_error("Array size is incompatible");
        }

        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] += rhs.buffer_[i];
        }
        return *this;
    }
};
} // namespace matrix