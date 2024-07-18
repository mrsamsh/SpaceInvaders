//
// Clock.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 15.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Clock.hpp"

#include <chrono>

namespace si
{

using clock = std::chrono::high_resolution_clock;
using time_point = std::chrono::high_resolution_clock::time_point;

time_point start = clock::now();

f32 Clock::Now()
{
  return (clock::now() - start).count() * 1.e-9f;
}

f32 Clock::Reset()
{
  f32 result = Now();
  start = clock::now();
  return result;
}

} // namespace si
