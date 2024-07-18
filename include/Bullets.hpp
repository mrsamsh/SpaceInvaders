//
// Bullets.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef BULLETS_HPP_
#define BULLETS_HPP_

#include "Entity.hpp"
#include "Shape.hpp"
#include <vector>

namespace si
{

struct Bullet : public Entity
{
  enum class Type { Player, Enemy } type;
  bool alive = true;
  u8 animation = 0;

  math::Rect getBoundingBox() const;
};

class Bullets
{
public:
  void add(math::vec2 pos, Color color, Bullet::Type type);
  void update(f32 const delta);
  void draw() const;
  std::vector<math::vec2> checkBounds(f32 top, f32 bottom);
  std::vector<Bullet> bullets;
private:
  static constexpr f32 speed = 100.f;
  u8 m_accumulator = 0;
};

} // namespace si

#endif // BULLETS_HPP_
