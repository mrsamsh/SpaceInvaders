//
// Game.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL2/SDL.h>
#include <string_view>

#include "Shape.hpp"
#include "Color.hpp"
#include "Vector.hpp"
#include "StateManager.hpp"

namespace si
{

class Game
{
public:
  void run();
public:
private:
  bool init();
  void handleEvents();
  void update(f32 const delta);
  void draw();
  void quit();

private:
  void handleResize();

  math::ivec2 m_windowSize;
  StateManager m_stateManager;
  bool m_running;
  bool m_renderFPS = false;
  bool m_resized = false;

public:
  static constexpr f32 Delta = 1.f / 60.f;
  static u32 HighScore;
  static bool NewHighScore;
private:
  static constexpr u32 Scale = 3;
};

} // namespace si

#endif // GAME_HPP_
