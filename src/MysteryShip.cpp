//
// MysteryShip.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 12.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "MysteryShip.hpp"
#include "GameContext.hpp"
#include "Render.hpp"

namespace si
{

MysteryShip::MysteryShip()
: Entity({{0, 20}, {0, 0}, 24, Color::Red})
{ }

void MysteryShip::spawn(MysteryShip::Direction direction)
{
  alive = true;
  switch (direction)
  {
  case Direction::ToLeft:
  {
    position.x = -16;
    velocity.x = 1;
  } break;
  case Direction::ToRight:
  {
    position.x = GameContext::WindowSize.x;
    velocity.x = -1;
  } break;
  }
}

void MysteryShip::update(f32 const delta)
{
  if (alive)
    position += velocity * delta * speed;
  else
    timer += delta;
}

void MysteryShip::draw() const
{
  if (alive)
    Render::sprite(position, color, sprite);
}

math::Rect MysteryShip::getBoundingBox() const
{
  return {position.x + 1, position.y, 14, 9};
}

} // namespace si
