//
// Sandbag.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 09.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef SANDBAG_HPP_
#define SANDBAG_HPP_

#include "Vector.hpp"
#include "Shape.hpp"
#include <vector>

namespace si
{

struct Bullet;

struct SandbagPiece
{
  math::Rect rect;
  bool alive = true;
};

struct Sandbag
{
  void init(math::vec2 const position);
  std::vector<SandbagPiece> pieces;
  math::Rect getBoundingBox() const;
  void reset();
  void handleBulletCollision(Bullet& b);
  void draw() const;
  math::vec2 position;
};

} // namespace si

#endif // SANDBAG_HPP_
