#ifndef TBM_UTILS_GEOMETRY_TYPES_H_
#define TBM_UTILS_GEOMETRY_TYPES_H_

namespace tbm {

template<typename T>
struct Rect {
 public:
  T left;
  T top;
  T width;
  T height;
};

}  // namespace tbm

#endif  // TBM_UTILS_GEOMETRY_TYPES_H_
