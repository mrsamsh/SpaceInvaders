//
// Enemy.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Enemy.hpp"
#include "Render.hpp"
#include "Game.hpp"
#include "Rand.hpp"
#include <iostream>

namespace si
{

Enemy::Enemy(math::vec2 const pos, Enemy::Type type)
: Entity{pos, math::vec2{1, 0}, static_cast<usz>(type)}
, type{type}
, accumulator{0.f}
{
  switch(type)
  {
  case Enemy::Type::Squid: {
    color = Color::White;
  } break;
  case Enemy::Type::Fly: {
    color = Color::Yellow;
  } break;
  case Enemy::Type::Octopus: {
    color = Color::Blue;
  } break;
  }
}

void Enemy::update(f32 const delta)
{
  sprite += (sprite == static_cast<usz>(type) ? 1 : -1);
  position += velocity;
}

void Enemy::draw() const
{
  Render::sprite(position, color, sprite);
}

math::Rect Enemy::getBoundingBox() const
{
  switch(type)
  {
  case Enemy::Type::Squid: {
    return {position.x + 4, position.y + 4, 8, 6};
  } break;
  case Enemy::Type::Octopus: {
    return {position.x + 3, position.y + 4, 10, 5};
  } break;
  case Enemy::Type::Fly: {
    return {position.x + 4, position.y + 4, 9, 5};
  } break;
  }
}

#include <iostream>
void EnemyFlock::spawn(math::vec2 position)
{
  enemies.clear();
  f32 offset = 16.f;
  for (int row = 4; row >= 0; --row)
  {
    for (int col = 0; col < 11; ++col)
    {
      Enemy::Type type;
      if (row == 0)                  type = Enemy::Type::Squid;
      else if (row == 1 || row == 2) type = Enemy::Type::Fly;
      else                           type = Enemy::Type::Octopus;
      enemies.push_back({position + math::vec2{col * offset, row * offset}, type});
    }
  }
  current_update = 0;
}

void EnemyFlock::update(f32 const delta)
{
  cooldown += delta;
  static f32 accumulator = 0;
  accumulator += delta;
  if (accumulator < Game::Delta)
  {
    return;
  }
  accumulator = 0;
  eraseDead();
  auto& e = enemies[current_update++];
  e.update(delta);
  if (e.position.x < 10 || e.position.x > 212)
  {
    changeDir = true;
  }
  if (current_update >= enemies.size())
  {
    current_update = 0;
  }
  if (changeDir && current_update == 0)
  {
    changeDir = false;
    std::for_each(enemies.begin(), enemies.end(), [](Enemy& e){
        e.velocity.x *= -1;
        e.position.y += 8;
      });
  }
}

void EnemyFlock::eraseDead()
{
  if (enemies.size() == 0)
    return;
  decltype(current_update) count = 0;
  for (usz i = 0; i < current_update; ++i)
  {
    if (enemies[i].alive == false) count++;
  }
  std::erase_if(enemies, [](Enemy const& e) { return !e.alive; });
  current_update -= count;
}

void EnemyFlock::draw() const
{
  std::for_each(enemies.begin(), enemies.end(), std::mem_fn(&Enemy::draw));
  // for (auto const& e : enemies)
  // {
  //   e.draw();
  // }
}

std::vector<math::vec2> EnemyFlock::getBottomRowPositions()
{
  std::vector<math::vec2> result;
  if (enemies.size() == 0) return result;
  math::vec2 first = enemies[0].position;
  result.push_back(first);
  for (usz i = 1; (i < enemies.size()) && (result.size() < 11); ++i)
  {
    math::vec2& currentPos = enemies[i].position;
    if (currentPos.y == first.y)
    {
      result.push_back(currentPos);
    }
    else
    {
      if (std::find_if(result.begin(), result.end(),
            [&currentPos](math::vec2 const& position){
              return std::abs(currentPos.x - position.x) < 2;
            }) == result.end())
      {
        result.push_back(currentPos);
      }
    }
  }
  return result;
}

void EnemyFlock::shootBullet(Bullets& bullets)
{
  auto candidates = getBottomRowPositions();
  auto position = math::rng::chooseOne(std::span{candidates});
  auto colors = {Color::White, Color::Yellow, Color::Red};
  auto color = math::rng::chooseOne(std::span{colors});
  bullets.add(position, color, Bullet::Type::Enemy);
}

} // namespace si
