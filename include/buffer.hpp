#include <utility>

namespace matrix {

template <typename T> class Buffer {
protected:
    T *buffer_ = nullptr;
    size_t size_ = 0;
    size_t used_ = 0;

    explicit Buffer(size_t size = 0)
        : buffer_((size == 0) ? nullptr : static_cast<T *>(::operator new(sizeof(T) * size))),
          size_(size), used_(0) {}

    Buffer(const Buffer<T> &) = delete;
    Buffer(Buffer<T> &&rhs) noexcept : buffer_(rhs.buffer_), size_(rhs.size_), used_(rhs.used_) {
        rhs.buffer_ = nullptr;
        rhs.size_ = 0;
        rhs.used_ = 0;
    }

    Buffer<T> &operator=(const Buffer<T> &) = delete;
    Buffer<T> &operator=(Buffer<T> &&rhs) noexcept {
        std::swap(buffer_, rhs.buffer_);
        std::swap(size_, rhs.size_);
        std::swap(used_, rhs.used_);
        return *this;
    }

    ~Buffer() noexcept {
        destroy(buffer_, buffer_ + used_);
        ::operator delete(buffer_);
    }

    static void construct(T *p, const T &val) {
        new (p) T(val);
    }

    static void destroy(T *p) noexcept {
        p->~T();
    }

    template <typename FwdIt> static void destroy(FwdIt begin, FwdIt end) noexcept {
        while (begin != end) {
            destroy(&*begin);
            ++begin;
        }
    }
};
} // namespace matrix