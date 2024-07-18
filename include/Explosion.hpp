//
// Explosion.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 10.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "Entity.hpp"
#include <vector>

namespace si
{

enum class ExplosionType
{
  SpaceShip,
  Bullet,
};

struct Explosion : public Entity
{
  ExplosionType type;
  u8 counter = 0;
  bool alive = true;
  void update(f32 const delta);
  void draw() const;
};

struct Explosions
{
  std::vector<Explosion> explosions;
  void addExplosion(math::vec2 pos, ExplosionType type);
  void update(f32 const delta);
  void draw() const;
};

} // namespace si

#endif // EXPLOSION_HPP_
