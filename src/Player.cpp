//
// Player.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Player.hpp"
#include "GameContext.hpp"
#include "Render.hpp"

namespace si
{

Player::Player()
: Entity{{GameContext::WindowSize.x / 2.f - 8, 180}, math::vec2{}, 25, Color::Green}
, alive{true}
{ }

void Player::spawn(math::vec2 const pos)
{
  alive = true;
  position = pos;
}

void Player::update(f32 const delta)
{
  if (alive)
  {
    position += velocity * 80.f * delta;
    position.x = math::clamp(position.x, 2.f, GameContext::WindowSize.x - 18.f);
  }
  else
  {
    static u32 counter = 0;
    static f32 accumulator = 0.f;
    accumulator += delta;
    if (accumulator >= GameContext::Delta)
    {
      counter++;
      accumulator = 0;
    }
    if (counter % 5 == 0)
    {
      sprite = 26 + (counter / 5) % 2;
    }
    if (counter == 90)
    {
      counter = 0;
      reset();
    }
  }
  cooldown += delta;
}

void Player::reset()
{
  alive = true;
  sprite = 25;
}

void Player::draw() const
{
  Render::sprite(position, color, sprite);
}

math::Rect Player::getBoundingBox() const
{
  return {position.x + 2, position.y + 6, 13, 5};
}

} // namespace si
