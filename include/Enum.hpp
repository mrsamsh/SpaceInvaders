//
// Enum.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 26.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef ENUM_HPP_
#define ENUM_HPP_

#include <concepts>

namespace si
{

template <typename T>
concept Enumurator = std::is_enum_v<T>;

template <Enumurator T>
[[nodiscard]] static inline constexpr
std::underlying_type_t<T> underlying(T t)
{
  return static_cast<std::underlying_type_t<T>>(t);
}

template <Enumurator T>
class Enum
{
public:
  using value_type = T;
  using underlying_type = std::underlying_type_t<T>;
  constexpr Enum(T t) : m_value{t} { }
  inline constexpr Enum& operator=(T t) { m_value = t; return *this; }
  inline constexpr operator T&() { return m_value; }
  inline constexpr operator T const&() const { return m_value; }
  inline constexpr operator underlying_type() const { return underlying(m_value); }
private:
  T m_value;
};

} // namespace si

#endif // ENUM_HPP_
