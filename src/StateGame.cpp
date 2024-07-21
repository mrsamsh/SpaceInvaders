//
// StateGame.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateGame.hpp"
#include "Game.hpp"
#include "Rand.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include <format>

using math::vec2;

namespace si
{

StateGame::StateGame(StateManager& manager)
: State(manager, StateID::Game)
, m_enemySpawnPosition{20, 32}
{
  init();
}

void StateGame::levelUp()
{
  m_enemies.spawn(m_enemySpawnPosition);
  m_player.spawn(PlayerSpawnPosition);
  m_enemySpawnPosition.y += 8;
  m_mysteryShip.timer = 0;
  m_mysteryShip.alive = false;
  m_level++;
  m_resetLevel = false;
}

void StateGame::init()
{
  m_enemies.spawn(m_enemySpawnPosition);
  m_player.spawn(PlayerSpawnPosition);

  for (int i = 0; i < 4; ++i)
  {
    auto init_x = 24.f;
    auto s_width = 30.f;
    auto y = 152.f;
    auto offset = (240.f - (init_x * 2.f + s_width)) / 3.f;
    m_sandbags[i].init(vec2{init_x + offset * i, y});
  }
  m_enemySpawnPosition.y += 8;
  m_mysteryShip.timer = 0;
  m_mysteryShip.alive = false;
  m_level++;
}

bool StateGame::update(f32 const delta)
{
  if (m_resetLevel)
    levelUp();

  updateActors(delta);
  checkAndResolveCollision();

  if (m_score >= m_scoreToRest)
  {
    m_rest++;
    m_scoreToRest += 1000;
  }

  return false;
}
void StateGame::draw() const
{
  m_player.draw();
  m_enemies.draw();
  for (auto& s : m_sandbags)
    s.draw();
  m_bullets.draw();
  m_explosions.draw();
  m_mysteryShip.draw();

  // HUD
  Render::fillRect({0, 0, 240, 12}, Color::Black);
  Render::fillRect({0, 188, 240, 12}, Color::Black);
  Render::drawText({26, 3}, Color::White,
      std::format("SCORE {:05}        LEVEL {:02}", m_score, m_level));
  f32 xx;
  for (int i = 0; i < m_rest; ++i)
  {
    static Color transGreen(0x557d55ff);
    xx = 6 + i * 16;
    Render::sprite({xx, 186}, transGreen, 25);
  }
  Render::drawText({xx + 20, 190}, Color::White, std::format("{}", m_rest));
  if (m_playerCanShoot)
    Render::fillRect({10, 10, 10, 10}, Color::Green);
  else
    Render::fillRect({10, 10, 10, 10}, Color::Red);
}

void StateGame::clearLevel()
{
  m_bullets.bullets.clear();
  m_explosions.explosions.clear();
  m_resetLevel = true;
  m_manager.requestStateChange(StateChange::Push, StateID::Clear);
  m_mysteryShip.alive = false;
}

void StateGame::updateActors(f32 const delta)
{
  m_player.velocity = { 0, 0 };
  if (Input::isKeyPressed(Key::Left))
    m_player.velocity.x -= 1;
  if (Input::isKeyPressed(Key::Right))
    m_player.velocity.x += 1;

  m_player.update(delta);
  if (m_player.alive)
  {
    if (m_playerDown)
    {
      reviveOrGameOver();
    }
    if (m_enemies.enemies.size() > 0)
      m_enemies.update(delta);
    else
    {
      // win state
      clearLevel();
    }
    m_bullets.update(delta);

    if (m_mysteryShip.timer > 10)
    {
      if (math::rng::generate<int>(1, 6) == 3)
      {
        spawnMysteryShip();
      }
      else
      {
        m_mysteryShip.timer -= 2;
      }
    }

    m_mysteryShip.update(delta);
    if (m_mysteryShip.position.x < -16 || m_mysteryShip.position.x > 240)
    {
      m_mysteryShip.alive = false;
    }

    auto const r = math::rng::generate<int>(0, 8);
    if (r == 4 && m_enemies.cooldown > 0.35)
    {
      m_enemies.cooldown = 0;
      m_enemies.shootBullet(m_bullets);
    }

    if (Input::isKeyPressed(Key::Fire)
        && m_player.cooldown > PlayerCooldownTime
        && m_playerCanShoot)
    {
      m_bullets.add(m_player.position, Color::White, Bullet::Type::Player);
      m_player.cooldown = 0;
      m_playerCanShoot = false;
    }
  }

  m_explosions.update(delta);

  auto bulletOutOfBounds = m_bullets.checkBounds(16, 176);
  for (auto& pos : bulletOutOfBounds)
  {
    if (pos.x < 0)
      m_playerCanShoot = true;
    else
      m_explosions.addExplosion(pos, ExplosionType::Bullet);
  }
}

void StateGame::checkAndResolveCollision()
{
  /* Collision ------------------------------------------- */
  /* ----------------------------------------------------- */

  for (int i = 0; i < m_bullets.bullets.size(); ++i)
  {
    Bullet& b = m_bullets.bullets[i];

    // Bullets with bullets
    for (int j = 0; j < m_bullets.bullets.size(); ++j)
    {
      if (i == j) continue;
      Bullet& b2 = m_bullets.bullets[j];
      if (b.type != b2.type && 
          math::Collision::check_intersection(
            b.getBoundingBox(), b2.getBoundingBox()
            ))
      {
        if (b.type == Bullet::Type::Player)
        {
          b.alive = false;
          m_playerCanShoot = true;
        }
        if (b2.type == Bullet::Type::Player)
        {
          m_playerCanShoot = true;
          b2.alive = false;
        }
        m_explosions.addExplosion(b.position, ExplosionType::Bullet);
      }
    }

    // bullets with sandbags
    for (auto& s : m_sandbags)
    {
      if (math::Collision::check_intersection(b.getBoundingBox(), s.getBoundingBox()))
      if (b.type == Bullet::Type::Player)
      {
        m_playerCanShoot = true;
      }
        s.handleBulletCollision(b);
    }

    // enemy bullets with player
    if (b.type == Bullet::Type::Enemy)
    {
      if(math::Collision::check_intersection(b.getBoundingBox(), m_player.getBoundingBox()))
      {
        b.alive = false;
        m_player.alive = false;
        m_playerDown = true;
        m_mysteryShip.alive = false;
        m_bullets.bullets.clear();
        break;
      }
    } else {

      // player bullets with mysteryShip
      if (m_mysteryShip.alive &&
          math::Collision::check_intersection(b.getBoundingBox(), m_mysteryShip.getBoundingBox()))
      {
        m_explosions.addExplosion(m_mysteryShip.position, ExplosionType::SpaceShip);
        b.alive = false;
        m_playerCanShoot = true;
        m_mysteryShip.alive = false;
        m_score += 100;
      }

      // m_player bullets with m_enemies
      for (auto& e : m_enemies.enemies)
      {
        if (math::Collision::check_intersection(b.getBoundingBox(), e.getBoundingBox()))
        {
          b.alive = false;
          m_playerCanShoot = true;
          e.alive = false;
          m_explosions.addExplosion(e.position, ExplosionType::SpaceShip);
          switch(e.type)
          {
          case Enemy::Type::Squid: {
            m_score += 30;
          } break;
          case Enemy::Type::Fly: {
            m_score += 20;
          } break;
          case Enemy::Type::Octopus: {
            m_score += 10;
          } break;
          }
        }

      }
    }
  }
}

void StateGame::spawnMysteryShip()
{
  m_mysteryShip.timer = 0;
  static MysteryShip::Direction directions[] = {
    MysteryShip::Direction::ToLeft,
    MysteryShip::Direction::ToRight
  };
  auto dir = math::rng::chooseOne(std::span{directions});
  m_mysteryShip.spawn(dir);
}

void StateGame::reviveOrGameOver()
{
  if (--m_rest == 0)
  {
    if (Game::HighScore < m_score)
    {
      Game::HighScore = m_score;
      Game::NewHighScore = true;
    }
    return gameOver();
  }
  else
  {
    for (auto& s : m_sandbags)
      s.reset();
    m_player.spawn(PlayerSpawnPosition);
    m_playerDown = false;
  }
}

void StateGame::gameOver()
{
  m_manager.requestStateChange(StateChange::Pop);
  m_manager.requestStateChange(StateChange::Push, StateID::GameOver);
}

} // namespace si
