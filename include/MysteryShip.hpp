//
// MysteryShip.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 12.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef MYSTERYSHIP_HPP_
#define MYSTERYSHIP_HPP_

#include "Entity.hpp"
#include "Shape.hpp"

namespace si
{

struct MysteryShip : public Entity
{
  enum class Direction { ToLeft = 0, ToRight };
  MysteryShip();
  void spawn(Direction direction);
  void update(f32 const delta);
  void draw() const;
  math::Rect getBoundingBox() const;
  f32 timer = 0;
  bool alive = false;
  static constexpr f32 speed = 100;
};

} // namespace si

#endif // MYSTERYSHIP_HPP_
