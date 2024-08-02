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
#include "SoundPlayer.hpp"
#include "GameContext.hpp"
#include <fmt/core.h>

using math::vec2;

namespace si
{

math::vec2 StateGame::PlayerSpawnPosition(GameContext::WindowSize.x / 2.f - 8, GameContext::WindowSize.y - 26);
f32 StateGame::PlayerCooldownTime = 0.35f;

StateGame::StateGame(StateManager& manager)
: State(manager, StateID::Game)
, m_enemySpawnPosition{20, 32}
{
  init();
}

void StateGame::levelUp()
{
  m_enemies.spawn(m_enemySpawnPosition);
  setSoundSpeed();
  m_player.spawn(PlayerSpawnPosition);
  m_enemySpawnPosition.y += 8;
  m_mysteryShip.timer = 0;
  m_mysteryShip.alive = false;
  m_level++;
  m_resetLevel = false;
}

void StateGame::setSoundSpeed()
{
  m_soundSpeed = std::log10((m_enemies.enemies.size() + 6) / 3);
}

void StateGame::init()
{
  m_enemies.spawn(m_enemySpawnPosition);
  m_player.spawn(PlayerSpawnPosition);
  setSoundSpeed();

  for (int i = 0; i < 4; ++i)
  {
    auto init_x = GameContext::WindowSize.x / 10.f;
    auto s_width = 30.f;
    auto y = GameContext::WindowSize.y - 48.f;
    auto offset = (GameContext::WindowSize.x - (init_x * 2.f + s_width)) / 3.f;
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
  Render::fillRect({0, 0, GameContext::WindowSize.x, 12}, Color::Grey);
  Render::fillRect({0, GameContext::WindowSize.y - 12, GameContext::WindowSize.x, 12}, Color::Grey);
  Render::drawText({floor((GameContext::WindowSize.x - 189.f) / 2), 3}, Color::White,
      fmt::format("SCORE {:05}        LEVEL {:02}", m_score, m_level));
  f32 xx = 10;
  Render::drawText({xx, GameContext::WindowSize.y - 10}, Color::White, fmt::format("{}", m_rest - 1));
  for (int i = 0; i < m_rest - 1; ++i)
  {
    static Color transGreen(0x557d55ff);
    xx = 20 + i * 16;
    Render::sprite({xx, GameContext::WindowSize.y - 14}, transGreen, 25);
  }
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
      SoundPlayer::stop(SoundChannel::Mystery);
    }
    static f32 soundAccumulator = 0;
    static i32 currentNote = 0;
    soundAccumulator += delta;
    if (soundAccumulator >= m_soundSpeed)
    {
      soundAccumulator = 0;
      SoundPlayer::play(static_cast<SoundEffect>(currentNote));
      currentNote = (currentNote + 1) % 4;
    }
    m_bullets.update(delta);

    if (m_mysteryShip.timer > 10)
    {
      if (math::rng::generate<int>(1, 6) == 3)
      {
        spawnMysteryShip();
        SoundPlayer::play(SoundEffect::Mystery, 5);
      }
      else
      {
        m_mysteryShip.timer -= 2;
      }
    }

    m_mysteryShip.update(delta);
    if (m_mysteryShip.position.x < -16 || m_mysteryShip.position.x > GameContext::WindowSize.x)
    {
      m_mysteryShip.alive = false;
    }

    auto const r = math::rng::generate<int>(0, 8);
    if (r == 4 && m_enemies.cooldown > 0.35)
    {
      m_enemies.cooldown = 0;
      m_enemies.shootBullet(m_bullets);
      // SoundPlayer::play(SoundEffect::Shoot2);
    }

    if (Input::isKeyPressed(Key::Fire)
        && m_player.cooldown > PlayerCooldownTime)
    {
      m_bullets.add(m_player.position, Color::White, Bullet::Type::Player);
      m_player.cooldown = 0;
      SoundPlayer::play(SoundEffect::Shoot1);
    }
  }

  m_explosions.update(delta);

  auto bulletOutOfBounds = m_bullets.checkBounds(12, GameContext::WindowSize.y - 24);
  for (auto& pos : bulletOutOfBounds)
  {
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
    if (b.alive != true)
      continue;

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
        }
        if (b2.type == Bullet::Type::Player)
        {
          b2.alive = false;
        }
        m_explosions.addExplosion(b.position, ExplosionType::Bullet);
      }
    }

    // bullets with sandbags
    for (auto& s : m_sandbags)
    {
      if (math::Collision::check_intersection(b.getBoundingBox(), s.getBoundingBox()))
      {
        if (s.handleBulletCollision(b))
          m_explosions.addExplosion(b.position, ExplosionType::Bullet);
      }
    }

    // enemy bullets with player
    if (b.type == Bullet::Type::Enemy)
    {
      if(math::Collision::check_intersection(b.getBoundingBox(), m_player.getBoundingBox()))
      {
        SoundPlayer::play(SoundEffect::Explosion2);
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
        m_mysteryShip.alive = false;
        m_score += (math::rng::generate(0, 4) + 6) * 10;
        SoundPlayer::stop(SoundChannel::Mystery);
        SoundPlayer::play(SoundEffect::Explosion1);
      }

      // m_player bullets with m_enemies
      for (auto& e : m_enemies.enemies)
      {
        if (math::Collision::check_intersection(b.getBoundingBox(), e.getBoundingBox()))
        {
          b.alive = false;
          e.alive = false;
          m_explosions.addExplosion(e.position, ExplosionType::SpaceShip);
          SoundPlayer::play(SoundEffect::Explosion1);
          setSoundSpeed();
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
    if (GameContext::HighScore < m_score)
    {
      GameContext::HighScore = m_score;
      GameContext::NewHighScore = true;
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
