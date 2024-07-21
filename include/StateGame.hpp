//
// StateGame.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef STATEGAME_HPP_
#define STATEGAME_HPP_

#include "State.hpp"
#include "Bullets.hpp"
#include "Explosion.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "MysteryShip.hpp"
#include "Sandbag.hpp"
#include <array>

namespace si
{

class StateGame : public State
{
public:
  StateGame(StateManager& manager);
  virtual bool update(f32 const delta) override;
  virtual void draw() const override;

private:
  void init();
  void clearLevel();
  void levelUp();
  void updateActors(f32 const delta);
  void checkAndResolveCollision();
  void spawnMysteryShip();
  void reviveOrGameOver();
  void gameOver();
  Bullets m_bullets;
  Explosions m_explosions;
  Player m_player;
  EnemyFlock m_enemies;
  MysteryShip m_mysteryShip;
  std::array<Sandbag, 4> m_sandbags;
  math::vec2 m_enemySpawnPosition;
  u32 m_score = 0;
  u8 m_level = 0;
  u8 m_rest = 3;
  u32 m_scoreToRest = 1000;
  bool m_resetLevel = false;
  bool m_playerDown = false;
  bool m_playerCanShoot = true;

  static constexpr f32 PlayerCooldownTime = 0.25;
  static constexpr math::vec2 PlayerSpawnPosition{112, 174};
};

} // namespace si

#endif // STATEGAME_HPP_
