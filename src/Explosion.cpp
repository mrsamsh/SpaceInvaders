//
// Explosion.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 10.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Explosion.hpp"
#include "Render.hpp"
#include "GameContext.hpp"

namespace si
{

void Explosion::update(f32 const delta)
{
  static f32 accumulator = 0;
  accumulator += delta;
  if (accumulator < GameContext::Delta)
    return;
  accumulator = 0;
  switch(type)
  {
  case ExplosionType::Bullet: {
    if (counter == 1)
    {
      sprite++;
      color = Color::Yellow;
    }
  }
  default:
    if (counter == 2)
      alive = false;
    break;
  }
  counter++;
}

void Explosion::draw() const
{
  Render::sprite(position, color, sprite);
}

void Explosions::addExplosion(math::vec2 pos, ExplosionType type)
{
  switch(type)
  {
  case ExplosionType::Bullet: {
    explosions.push_back({
      pos, {}, 6, Color::Red,
      type
    });
  } break;
  case ExplosionType::SpaceShip: {
    explosions.push_back({
      pos, {}, 14, Color::White,
      type
    });
  } break;
  }
}

void Explosions::update(f32 const delta)
{
  std::erase_if(explosions, [](Explosion const& e) { return e.alive == false; });
  std::for_each(explosions.begin(), explosions.end(), [&delta](Explosion& e)
      {
        e.update(delta);
      });
}

void Explosions::draw() const
{
  std::for_each(explosions.begin(), explosions.end(), [](Explosion const& e)
      {
        e.draw();
      });
}

} // namespace si
