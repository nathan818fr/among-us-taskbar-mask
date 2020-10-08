#ifndef TBM_UTILS_MATH_UTILS_H_
#define TBM_UTILS_MATH_UTILS_H_

#include <cmath>
#include <algorithm>

namespace tbm {

template<typename R, typename T>
inline static R ncast(T value) {
  return static_cast<R>(value);
}

template<typename R, typename T>
inline static R round(T value) {
  return static_cast<R>(std::round(value));
}

template<typename R, typename T>
inline static R ceil(T value) {
  return static_cast<R>(std::ceil(value));
}

template<typename T>
inline static T clamp(T value, T min, T max) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

template<typename T>
inline static T center(T content_size, T container_size) {
  return (container_size - content_size) / 2;
}

}  // namespace tbm

#endif  // TBM_UTILS_MATH_UTILS_H_
