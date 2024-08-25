//
// EnumWrapper.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 26.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef ENUM_WRAPPER_HPP_
#define ENUM_WRAPPER_HPP_

#include <concepts>

namespace si
{

namespace enm
{

template <typename T>
concept Enumurator = std::is_enum_v<T>;

template <auto E>
struct underlying;

template <Enumurator Enum, Enum E>
struct underlying<E>
{
  using enum_type = Enum;
  static constexpr std::underlying_type_t<Enum> value = static_cast<std::underlying_type_t<Enum>>(E);
};

template <auto E>
inline constexpr auto underlying_v = underlying<E>::value;

template <Enumurator Enum>
[[nodiscard]] static inline constexpr
std::underlying_type_t<Enum> getUnderlying(Enum e)
{
  return static_cast<std::underlying_type_t<Enum>>(e);
}


} // namespace enum

template <enm::Enumurator T>
class EnumWrapper
{
public:
  using value_type = T;
  using underlying_type = std::underlying_type_t<T>;
  constexpr EnumWrapper(T t) : m_value{t} { }
  inline constexpr EnumWrapper& operator=(T t) { m_value = t; return *this; }
  inline constexpr operator T&() { return m_value; }
  inline constexpr operator T const&() const { return m_value; }
  inline constexpr operator underlying_type() const { return enm::getUnderlying(m_value); }
private:
  T m_value;
};

} // namespace si

#endif // ENUM_WRAPPER_HPP_
