//
// Color.hpp
// include
//
// Created by Usama Alshughry 27.08.2023.
// Copyright © 2023 Usama Alshughry. All rights reserved
//

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "MyTypes.hpp"
#include "Vector.hpp"

namespace si
{

struct Color
{
  u8 r, g, b, a;

  [[nodiscard]] constexpr Color() : r(0xff), g(0xff), b(0xff), a(0xff) { }
  [[nodiscard]] constexpr Color(const u32 c)
      : r((c >> 24))
      , g((c >> 16) & 0xff)
      , b((c >> 8) & 0xff)
      , a(c & 0xff)
  {
  }
  [[nodiscard]] constexpr Color(const u8 red, const u8 green, const u8 blue,
                                const u8 alpha = 0xff)
      : r(red)
      , g(green)
      , b(blue)
      , a(alpha)
  {
  }

  [[nodiscard]] constexpr math::vec4T<f32> normalized() const
  {
    return math::vec4T<f32>(r, g, b, a).operator*=(NormDivisor);
  }

  static constexpr f32 NormDivisor = 1.f / 255.f;

  // Predefined Colors
  static const Color Red;
  static const Color Green;
  static const Color DifferentGreen;
  static const Color Blue;
  static const Color Yellow;
  static const Color White;
  static const Color Black;
  static const Color Brown;
  static const Color Grey;
};

} // namespace ge

#endif // COLOR_HPP_
