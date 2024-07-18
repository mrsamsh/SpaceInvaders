//
// MathConcepts.hpp
// ge4
//
// Created by Usama Alshughry 26.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef MATHCONCEPTS_HPP_
#define MATHCONCEPTS_HPP_

#include <concepts>

namespace math
{

namespace mcp
{
  template <typename T>
  concept Arithmetic = std::is_arithmetic_v<T>;

  template <typename T>
  concept FloatingPoint = std::is_floating_point_v<T>;

  template <typename T>
  concept Integral = std::is_integral_v<T>;

  template <typename T, typename ... Ts>
  concept IsAmong = (std::same_as<T, Ts> || ...);

} // namespace mcp

} // namespace math

#endif // MATHCONCEPTS_HPP_
