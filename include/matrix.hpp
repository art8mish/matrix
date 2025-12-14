#pragma once


#include <cstddef>
#include <concepts>
// #include <type_traits>

namespace matrix {

template <typename T> void construct(T *p, const T& val) {
    new (p) T(val);
}

template <typename T> void destroy(T *p) noexcept {
    p->~T();
}

template <typename FwdIt> void destroy(FwdIt begin, FwdIt end) noexcept {
    while (begin != end) {
        destroy<T>(&*begin);
        ++begin;
    }
}

template <typename T>
class Buf {
protected:
    T *buf_;
    size_t size_ {0};
    size_t used_ {0};

    explicit Buf(size_t size = 0) : buf_((size == 0) ? nullptr :
        static_cast<T *>(::operator new(sizeof(T) * size))), size_(size), used_(0) {}

    Buf(const Buf &) = delete;
    Buf(const Buf &&rhs) noexcept
        : buf_(rhs.buf_), size_(rhs.size_), used_(rhs.used_) {
        rhs.buf_ = nullptr;
        rhs.size_ = 0;
        rhs.used_ = 0;
    }

    Buf &operator=(const Buf &) = delete;
    Buf &operator=(const Buf &&rhs) noexcept {
        std::swap(buf_, rhs.buf_);
        std::swap(size_, rhs.size_);
        std::swap(used_, rhs.used_);
        return *this;
    }

    ~Buf() noexcept {
        destroy<T>(buf_, buf_ + used_);
        ::operator delete(buf_);
    }
};

template <std::floating_point T>
class Matrix : private Buf<T> {
    using Buf<T>::buf_;
    using Buf<T>::size_;
    using Buf<T>::used_;

    explicit Matrix(size_t size = 0) : Buf<T>(size) {}
    Matrix(Matrix &rhs) : Buf<T>(rhs.used_) {
        while (used_ != size_) {
            construct<T>(buf_ + used_, rhs.buf_[used_]);
            ++used_;
        }

    }
    Matrix(Matrix &&rhs) = default;
    Matrix &operator=(const Matrix &rhs) {
        if (this == &rhs)
            return *this;
        Matrix tmp{rhs};
        std::swap(*this, tmp);
        return *this;
    }
    Matrix &operator=(const Buf &&rhs) = default;
};


} // namespace matrix