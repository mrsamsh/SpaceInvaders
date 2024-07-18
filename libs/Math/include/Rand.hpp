//
// Rand.hpp
// ge4
//
// Created by Usama Alshughry 27.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef RAND_HPP_
#define RAND_HPP_

#include "MathHelper.hpp"
#include "MyTypes.hpp"
#include "MathConcepts.hpp"

#include <random>
#include <span>
#include <ranges>
#include <iostream>

namespace math
{

class rng
{
public:
  template <mcp::FloatingPoint T>
  inline static T generate(T const min, T const max)
  {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(gen);
  }

  template <mcp::Integral T>
  inline static T generate(T const min, T const max)
  {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(gen);
  }

  inline static u32 generate()
  {
    return gen();
  }

  template <mcp::FloatingPoint T>
  inline static T pseudoGenerate(T const min, T const max)
  {
    T const range = max - min;
    return (static_cast<T>(rand()) / static_cast<T>(RAND_MAX)) * range + min;
  }

  template <mcp::Integral T>
  inline static T pseudoGenerate(T const min, T const max)
  {
    T const range = max - min;
    return (rand() % range) + min;
  }

  template <typename T, usz N>
  inline static void shuffle(std::span<T, N> aSpan)
  {
    std::ranges::shuffle(aSpan, gen);
  }

  template <typename T, usz N>
  inline static T chooseOne(std::span<T, N> aSpan)
  {
    return aSpan[generate<usz>(0, aSpan.size() - 1)];
  }

private:
  static std::random_device rd;
  static std::mt19937 gen;
};

} // namespace math

#endif // RAND_HPP_
