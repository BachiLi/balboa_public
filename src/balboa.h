#pragma once

// CMake inserts NDEBUG when building with RelWithDebInfo
// This is an ugly hack to undo that...
#undef NDEBUG

#include <cassert>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <algorithm>

// for suppressing unused warnings
#define UNUSED(x) (void)(x)

// We use double for most of our computation.
// Computer Graphics is usually done in single precision Reals.
// However, torrey is an educational renderer with does not
// put emphasis on the absolute performance. 
// We choose double so that we do not need to worry about
// numerical accuracy as much when we render.
// Switching to floating point computation is easy --
// just set Real = float.
using Real = double;

const Real c_PI = Real(3.14159265358979323846);

template <typename T>
inline T infinity() {
    return std::numeric_limits<T>::infinity();
}

namespace fs = std::filesystem;

inline std::string to_lowercase(const std::string &s) {
    std::string out = s;
    std::transform(s.begin(), s.end(), out.begin(), ::tolower);
    return out;
}

template <typename T>
inline T max(const T &a, const T &b) {
    return a > b ? a : b;
}

template <typename T>
inline T min(const T &a, const T &b) {
    return a < b ? a : b;
}
