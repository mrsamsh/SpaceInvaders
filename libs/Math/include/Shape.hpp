//
// Shape.hpp
// ge2
//
// Created by Usama Alshughry 31.08.2023.
// Copyright © 2023 Usama Alshughry. All rights reserved
//

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "MathHelper.hpp"
#include "Vector.hpp"

namespace math
{

template <mcp::Arithmetic T>
struct CircleT
{
  [[nodiscard]] constexpr CircleT() : center(0, 0), r(0) { }
  [[nodiscard]] constexpr CircleT(const vec2T<T>& center_, const T r_)
      : center(center_)
      , r(r_)
  {
  }

  [[nodiscard]] constexpr CircleT(const T a, const T b, const T c)
      : center(a, b)
      , r(c)
  {
  }

  [[nodiscard]] constexpr CircleT(const CircleT& c)
      : center(c.center)
      , r(c.r)
  {
  }

  union
  {
    vec2T<T> center;
    struct { T x, y; };
  };
  T r;
};

template <mcp::Arithmetic T>
struct RectT
{
  [[nodiscard]] constexpr RectT() : position(0, 0), size(0, 0) { }
  [[nodiscard]] constexpr RectT(const T a, const T b, const T c, const T d)
      : position(a, b)
      , size(c, d)
  {
  }
  [[nodiscard]] constexpr RectT(const RectT& r)
      : position(r.position)
      , size(r.size)
  {
  }

  [[nodiscard]] inline constexpr T left()   const { return w >= 0 ? x : x + w; }
  [[nodiscard]] inline constexpr T right()  const { return w >= 0 ? x + w : x; }
  [[nodiscard]] inline constexpr T top()    const { return h >= 0 ? y : y + h; }
  [[nodiscard]] inline constexpr T bottom() const { return h >= 0 ? y + h : y; }

  union
  {
    struct { T x, y; };
    vec2T<T> position;
  };
  union
  {
    struct { T w, h; };
    vec2T<T> size;
  };
};

namespace Collision
{

  template <mcp::Arithmetic T>
  inline constexpr bool point_inside(const RectT<T>& r, const vec2T<T>& p)
  {
    return p.x >= r.left() && p.x <= r.right() &&
           p.y >= r.top()  && p.y <= r.bottom();
  }

  template <mcp::Arithmetic T>
  inline constexpr bool point_inside(const CircleT<T>& c, const vec2T<T>& p)
  {
    return (c.center - p).length2() < (c.r * c.r);
  }

  template<mcp::Arithmetic T>
  [[nodiscard]] inline constexpr RectT<T> calculate_minkowski(
      const RectT<T>& r1, const RectT<T>& r2)
  {
    return RectT<T>(
        r1.left() - r2.right(),
        r1.top()  - r2.bottom(),
        abs(r1.w) + abs(r2.w),
        abs(r1.h) + abs(r2.h)
    );
  }

  template <mcp::Arithmetic  T>
  inline constexpr bool check_intersection(const RectT<T>& r, const CircleT<T>& c)
  {
    vec2T<T> nearest(
       clamp(c.x, r.left(), r.right()),
       clamp(c.y, r.top(), r.bottom())
       );
    return point_inside(c, nearest);
  }

  template <mcp::Arithmetic  T>
  inline constexpr bool check_intersection(const RectT<T>& r1, const RectT<T>& r2)
  {
    return point_inside(calculate_minkowski(r1, r2), { 0, 0 });
  }

} // namespace Collision

using Rect = RectT<f32>;
using Circle = CircleT<f32>;

} // namespace math

#endif // SHAPE_HPP_
