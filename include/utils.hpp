#pragma once

#include <concepts>

namespace matrix {
template <std::floating_point T> T epsilon() {
    if (std::is_same_v<T, double>)
        return 1e-9;
    else if (std::is_same_v<T, long double>)
        return 1e-12;
    else
        return 1e-6f;
}
} // namespace matrix