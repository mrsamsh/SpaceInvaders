//
// Enemy.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "Entity.hpp"
#include "Color.hpp"
#include "Bullets.hpp"
#include "Shape.hpp"

#include <vector>

namespace si
{

struct Enemy : public Entity
{
  enum class Type
  {
    Squid = 0,
    Fly = 8,
    Octopus = 16
  };

  Enemy(math::vec2 const pos, Enemy::Type type);
  void update(f32 const delta);
  void draw() const;
  math::Rect getBoundingBox() const;
  Enemy::Type type;
  f32 accumulator;
  bool alive = true;
};

struct EnemyFlock
{
  void spawn(math::vec2 position);
  void shootBullet(Bullets& bullets);
  void update(f32 const delta);
  void draw() const;
  void eraseDead();
  std::vector<math::vec2> getBottomRowPositions();
  std::vector<Enemy> enemies;
  usz current_update;
  f32 cooldown = 0;
  bool changeDir = false;
};

} // namespace si

#endif // ENEMY_HPP_
