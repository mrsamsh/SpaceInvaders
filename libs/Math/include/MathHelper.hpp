//
// MathHelper.hpp
// ge4
//
// Created by Usama Alshughry 26.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef MATHHELPER_HPP_
#define MATHHELPER_HPP_

#include "MathConcepts.hpp"

namespace math
{

template <mcp::Arithmetic T>
inline constexpr
T abs(T a)
{
  return a >= 0 ? a : -a;
}

template <mcp::Arithmetic T>
inline constexpr
T min(T a, T b)
{
  return a <= b ? a : b;
}

template <mcp::Arithmetic T>
inline constexpr
T max(T a, T b)
{
  return a >= b ? a : b;
}

template <mcp::Arithmetic T>
inline constexpr
T clamp(T val, T minimum, T maximum)
{
  return min(maximum, max(val, minimum));
}

} // namespace math

#endif // MATHHELPER_HPP_
