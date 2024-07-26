//
// Sandbag.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 09.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Sandbag.hpp"
#include "Render.hpp"
#include "Shape.hpp"
#include "Bullets.hpp"

namespace si
{

static constexpr u8 Prototype[] = {
  0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
  0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
  1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
  1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
};

static constexpr u8 ExplosionPattern[] = {
  1,0,1,1,1,0,1,
  0,1,1,1,1,1,0,
  1,0,1,1,1,0,1,
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0,
  1,0,1,1,1,0,1
};

static constexpr u8 Width = 30;
static constexpr u8 Height = 14;
static constexpr f32 Side = 1.f;

static inline constexpr
void handleExplosion(std::vector<SandbagPiece>& pieces, int const x, int const y, bool bottom)
{
  pieces[x + y * Width].alive = false;
  int x_min = x - 3;
  int x_max = x + 3;
  int y_min = y;
  int y_max = y + 6;
  if (bottom)
  {
    y_min -= 6;
    y_max -= 6;
  }
  for (int grid_y = y_min, py = 0; grid_y <= y_max; ++grid_y, ++py)
  {
    for (int grid_x = x_min, px = 0; grid_x <= x_max; ++grid_x, ++px)
    {
      if (grid_x < 0 || grid_x >= Width || grid_y < 0 || grid_y >= Height)
        continue;
      if (ExplosionPattern[px + py * 7] == 1)
      {
        pieces[grid_x + grid_y * Width].alive = false;
      }
    }
  }
}

void Sandbag::init(math::vec2 const position)
{
  this->position = position;
  for (int y = 0; y < Height; ++y)
  {
    for (int x = 0; x < Width; ++x)
    {
      pieces.push_back({{
          position.x + x * Side,
          position.y + y * Side,
          Side,
          Side,
      }});
      if (Prototype[x + y * Width] != 1)
        pieces.back().alive = false;
    }
  }
}

void Sandbag::draw() const
{
  for (auto& [rect, alive] : pieces)
    if (alive)
      Render::fillRect(rect, Color::DifferentGreen);
  // Game::drawRect(getBoundingBox(), Color::Green);
}

math::Rect Sandbag::getBoundingBox() const
{
  return {position.x + 1, position.y, (Width * Side) - 2, Height * Side};
}

bool Sandbag::handleBulletCollision(Bullet& b)
{
  if (b.alive == false)
    return false;
  for (int y = 0; y < Height; ++y)
  {
    for (int x = 0; x < Width; ++x)
    {
      auto& piece = pieces[x + y * Width];
      if (piece.alive && math::Collision::check_intersection(piece.rect, b.getBoundingBox()))
      {
        // collision occured
        b.alive = false;
        handleExplosion(pieces, x, y, b.type == Bullet::Type::Player);
        return true;
      }
    }
  }
  return false;
}

void Sandbag::reset()
{
  for (int y = 0; y < Height; ++y)
  {
    for (int x = 0; x < Width; ++x)
    {
      if (Prototype[x + y * Width] == 1)
        pieces[x + y * Width].alive = true;
    }
  }
}

} // namespace si
