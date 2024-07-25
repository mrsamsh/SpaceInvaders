//
// Bullets.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Bullets.hpp"
#include "Render.hpp"
#include "Rand.hpp"

namespace si
{

math::Rect Bullet::getBoundingBox() const
{
  return {position.x + 6, position.y + 4, 3, 7};
}

void Bullets::add(math::vec2 pos, Color color, Bullet::Type type)
{
  switch (type)
  {
    case Bullet::Type::Player:
    {
      bullets.push_back({
          pos + math::vec2{1, -4},
          math::vec2{0, -2.5f},
          5,
          color,
          type,
      });
    } break;
    case Bullet::Type::Enemy:
    {
      auto const offset = math::rng::generate<usz>(0, 2) * 8;
      bullets.push_back({
          pos + math::vec2{0, 4},
          math::vec2{0, 0.8f},
          2 + offset,
          color,
          type,
      });
    } break;
  }
}

std::vector<math::vec2> Bullets::checkBounds(f32 top, f32 bottom)
{
  std::vector<math::vec2> result;
  std::for_each(bullets.begin(), bullets.end(), [top, bottom, &result](Bullet& bullet)
    {
      if (bullet.position.y < top || bullet.position.y > bottom)
      {
        bullet.alive = false;
        result.push_back(bullet.position);
      }
    });
  return result;
}

void Bullets::update(f32 const delta)
{
  m_accumulator++;
  std::erase_if(bullets, [](Bullet const& b) { return b.alive == false; });
  for (auto& bullet : bullets)
  {
    bullet.position += bullet.velocity * speed * delta;
    if (m_accumulator > 6 && bullet.alive && bullet.type == Bullet::Type::Enemy)
    {
      bullet.animation = (bullet.animation + 1) % 3;
    }
  }
  if (m_accumulator > 6)
    m_accumulator = 0;
}

void Bullets::draw() const
{
  for (auto const& bullet : bullets)
  {
    Render::sprite(bullet.position, bullet.color, bullet.sprite + bullet.animation);
    // Game::drawRect(bullet.getBoundingBox(), Color::Green);
  }
}

} // namespace si
