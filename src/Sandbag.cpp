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
  0,0,1,1,1,0,0,
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0,
  1,1,1,1,1,1,1,
  0,1,1,1,1,1,0,
  0,0,1,1,1,0,0
};

static constexpr u8 Width = 30;
static constexpr u8 Height = 14;
static constexpr f32 Side = 1.f;

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
        piece.alive = false;
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
