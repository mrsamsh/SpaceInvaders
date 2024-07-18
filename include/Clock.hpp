//
// Clock.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 15.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "MyTypes.hpp"

namespace si
{

struct Clock
{
  static f32 Now();
  static f32 Reset();
};

} // namespace si

#endif // CLOCK_HPP_
