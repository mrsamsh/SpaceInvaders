//
// Player.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Entity.hpp"
#include "Shape.hpp"

namespace si
{

struct Player : public Entity
{
  Player();
  void spawn(math::vec2 const position);
  void update(f32 const delta);
  void reset();
  void draw() const;
  math::Rect getBoundingBox() const;
  bool alive;
  f32 cooldown = 0.f;
};

} // namespace si

#endif // PLAYER_HPP_
