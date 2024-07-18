//
// Entity.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "Vector.hpp"
#include "Color.hpp"

namespace si
{

struct Entity
{
  math::vec2 position;
  math::vec2 velocity;
  usz  sprite;
  Color color;
};

} // namespace si


#endif // ENTITY_HPP_
