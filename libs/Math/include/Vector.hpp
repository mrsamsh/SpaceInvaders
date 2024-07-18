//
// Vector.hpp
// ge4
//
// Created by Usama Alshughry 26.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cmath>
#include <initializer_list>

#include "MyTypes.hpp"
#include "MathConcepts.hpp"
#include "MathHelper.hpp"

namespace math
{

template <mcp::Arithmetic T>
class vec2T
{
public:
  using value_type = T;
  constexpr vec2T() : x(0), y(0) { }
  constexpr vec2T(T a, T b) : x{a}, y{b} { }
  constexpr vec2T(vec2T const& v) : x{v.x}, y{v.y} { }

  template <mcp::Arithmetic U>
  constexpr vec2T(vec2T<U> const& v)
  requires(std::is_convertible_v<U, T>)
  : x{static_cast<T>(v.x)}
  , y{static_cast<T>(v.y)}
  { }

  // Modifying Operators
  inline constexpr
  vec2T& operator+=(vec2T const& v)
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  inline constexpr
  vec2T& operator-=(vec2T const& v)
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  inline constexpr
  vec2T& operator*=(T val)
  {
    x *= val;
    y *= val;
    return *this;
  }

  inline constexpr
  vec2T& operator/=(T val)
  {
    T const scalar = static_cast<T>(1) / val;
    x *= scalar;
    y *= scalar;
    return *this;
  }

  inline constexpr
  vec2T& operator*=(vec2T const& v)
  {
    x *= v.x;
    y *= v.y;
    return *this;
  }

  inline constexpr
  vec2T& operator/=(vec2T const& v)
  {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  inline constexpr
  T length2() const
  {
    return x * x + y * y;
  }

  inline constexpr
  T length() const
  {
    return std::sqrt(x * x + y * y);
  }

  [[nodiscard]] inline constexpr
  vec2T normalized() const
  {
    if (isZero())
    {
      return vec2T();
    }
    T const scalar = static_cast<T>(1) / length();
    return vec2T(x * scalar, y * scalar);
  }

  inline constexpr
  bool operator==(vec2T const& rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  inline constexpr
  bool operator!=(vec2T const& rhs) const
  {
    return x != rhs.x || y != rhs.y;
  }

  // Accessors
  inline constexpr
  T* data()
  {
    return elements;
  }

  inline constexpr
  T const* data() const
  {
    return elements;
  }

  inline constexpr
  T& operator[](i8 const i)
  {
    return elements[i];
  }

  inline constexpr
  T const& operator[](i8 const i) const
  {
    return elements[i];
  }

public:
  union
  {
    struct { T x, y; };
    struct { T u, v; };
    struct { T width, height; };
    T elements[2];
  };

private:
  inline constexpr
  bool isZero() const
  requires (mcp::FloatingPoint<T>)
  {
    return math::abs(x) < TinyBit
        && math::abs(y) < TinyBit;
  }

  inline constexpr
  bool isZero() const
  requires (mcp::Integral<T>)
  {
    return x == 0 
        && y == 0;
  }

  static constexpr T TinyBit = static_cast<T>(1.e-6);
};

template <mcp::Arithmetic T>
class vec3T
{
public:
  using value_type = T;
  constexpr vec3T() : x(0), y(0), z(0) { }
  constexpr vec3T(T a, T b, T c) : x{a}, y{b}, z{c} { }
  constexpr vec3T(vec3T const& v) : x{v.x}, y{v.y}, z{v.z} { }

  template <mcp::Arithmetic U>
  constexpr explicit vec3T(vec3T<U> const& v)
  : x{static_cast<T>(v.x)}
  , y{static_cast<T>(v.y)}
  , z{static_cast<T>(v.z)}
  { }

  // Modifying Operators
  inline constexpr
  vec3T& operator+=(vec3T const& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  inline constexpr
  vec3T& operator-=(vec3T const& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  inline constexpr
  vec3T& operator*=(T val)
  {
    x *= val;
    y *= val;
    z *= val;
    return *this;
  }

  inline constexpr
  vec3T& operator/=(T val)
  {
    T const scalar = static_cast<T>(1) / val;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  inline constexpr
  vec3T& operator*=(vec3T const& v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  inline constexpr
  vec3T& operator/=(vec3T const& v)
  {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  inline constexpr
  T length2() const
  {
    return x * x + y * y + z * z;
  }

  inline constexpr
  T length() const
  {
    return std::sqrt(x * x + y * y + z * z);
  }

  [[nodiscard]] inline constexpr
  vec3T normalized() const
  {
    if (isZero())
    {
      return vec3T();
    }
    T const scalar = static_cast<T>(1) / length();
    return vec3T(x * scalar, y * scalar, z * scalar);
  }

  inline constexpr
  bool operator==(vec3T const& rhs) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  inline constexpr
  bool operator!=(vec3T const& rhs) const
  {
    return x != rhs.x || y != rhs.y || z != rhs.z;
  }

  // Accessors
  inline constexpr
  T* data()
  {
    return elements;
  }

  inline constexpr
  T const* data() const
  {
    return elements;
  }

  inline constexpr
  T& operator[](i8 const i)
  {
    return elements[i];
  }

  inline constexpr
  T const& operator[](i8 const i) const
  {
    return elements[i];
  }

public:
  union
  {
    struct { T x, y, z; };
    struct { T width, height, depth; };
    T elements[3];
  };
private:
  T padding;

private:
  inline constexpr
  bool isZero() const
  requires (mcp::Integral<T>)
  {
    return x == 0
        && y == 0
        && z == 0;
  }

  inline constexpr
  bool isZero() const
  requires (mcp::FloatingPoint<T>)
  {
    return math::abs(x) < TinyBit
        && math::abs(y) < TinyBit
        && math::abs(z) < TinyBit;
  }

  static constexpr T TinyBit = static_cast<T>(1.e-6);
};

template <mcp::Arithmetic T>
class vec4T
{
public:
  using value_type = T;
  constexpr vec4T() : x(0), y(0), z(0), w(0) { }
  constexpr vec4T(T a, T b, T c, T d) : x{a}, y{b}, z{c}, w{d} { }
  constexpr vec4T(vec4T const& v) : x{v.x}, y{v.y}, z{v.z}, w{v.w} { }

  template <mcp::Arithmetic U>
  constexpr explicit vec4T(vec4T<U> const& v)
  : x{static_cast<T>(v.x)}
  , y{static_cast<T>(v.y)}
  , z{static_cast<T>(v.z)}
  , w{static_cast<T>(v.w)}
  { }

  // Modifying Operators
  inline constexpr
  vec4T& operator+=(vec4T const& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  inline constexpr
  vec4T& operator-=(vec4T const& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  inline constexpr
  vec4T& operator*=(T val)
  {
    x *= val;
    y *= val;
    z *= val;
    w *= val;
    return *this;
  }

  inline constexpr
  vec4T& operator/=(T val)
  {
    T const scalar = static_cast<T>(1) / val;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  inline constexpr
  vec4T& operator*=(vec4T const& v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }

  inline constexpr
  vec4T& operator/=(vec4T const& v)
  {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  inline constexpr
  T length2() const
  {
    return x * x + y * y + z * z + w * w;
  }

  inline constexpr
  T length() const
  {
    return std::sqrt(x * x + y * y + z * z + w * w);
  }

  [[nodiscard]] inline constexpr
  vec4T normalized() const
  {
    if (isZero())
    {
      return vec4T();
    }
    T scalar = static_cast<T>(1) / length();
    return vec4T(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  inline constexpr
  bool operator==(vec4T const& rhs) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
  }

  inline constexpr
  bool operator!=(vec4T const& rhs) const
  {
    return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
  }

  // Accessors
  inline constexpr
  T* data()
  {
    return elements;
  }

  inline constexpr
  T const* data() const
  {
    return elements;
  }

  inline constexpr
  T& operator[](i8 const i)
  {
    return elements[i];
  }

  inline constexpr
  T const& operator[](i8 const i) const
  {
    return elements[i];
  }

public:
  union
  {
    struct { T x, y, z, w; };
    T elements[4];
  };

private:
  inline constexpr
  bool isZero() const
  requires (mcp::FloatingPoint<T>)
  {
    return math::abs(x) < TinyBit
        && math::abs(y) < TinyBit
        && math::abs(z) < TinyBit
        && math::abs(w) < TinyBit;
  }

  inline constexpr
  bool isZero() const
  requires (mcp::Integral<T>)
  {
    return x == 0
        && y == 0
        && z == 0
        && w == 0;
  }
  static constexpr T TinyBit = static_cast<T>(1.e-6);
};

// Dot Products
template <mcp::Arithmetic T>
[[nodiscard]] inline constexpr
T dotProduct(vec2T<T> const& v1, vec2T<T> const& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

template <mcp::Arithmetic T>
[[nodiscard]] inline constexpr
T dotProduct(vec3T<T> const& v1, vec3T<T> const& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <mcp::Arithmetic T>
[[nodiscard]] inline constexpr
T dotProduct(vec4T<T> const& v1, vec4T<T> const& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// 3d Cross product
template <mcp::Arithmetic T>
[[nodiscard]] inline constexpr
vec3T<T> crossProduct(vec3T<T> const& v1, vec3T<T> const& v2)
{
  return vec3T<T>(
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x
  );
}

template <typename T>
concept Vector = (mcp::IsAmong<vec2T<T>, vec3T<T>, vec4T<T>>);

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator+(Vector<T> lhs, Vector<T> const& rhs)
{
  return lhs += rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator-(Vector<T> lhs, Vector<T> const& rhs)
{
  return lhs -= rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator*(Vector<T> lhs, typename Vector<T>::value_type rhs)
{
  return lhs *= rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator/(Vector<T> lhs, typename Vector<T>::value_type rhs)
{
  return lhs /= rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator*(Vector<T> lhs, Vector<T> const& rhs)
{
  return lhs *= rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> operator/(Vector<T> lhs, Vector<T> const& rhs)
{
  return lhs /= rhs;
}

template <mcp::Arithmetic T, template <typename> typename Vector>
[[nodiscard]] inline constexpr
Vector<T> lerp(Vector<T> const& v0, Vector<T> const& v1, typename Vector<T>::value_type const t)
{
  return v0 + (v1 - v0) * t;
}

using vec2 = vec2T<f32>;
using ivec2 = vec2T<i32>;

} // namespace math

#endif // VECTOR_HPP_
