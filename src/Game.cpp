//
// Game.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Game.hpp"
#include "StateGame.hpp"
#include "StateStart.hpp"
#include "StateClear.hpp"
#include "StateGameOver.hpp"
#include "Clock.hpp"
#include "Render.hpp"

#include <format>

namespace si
{

static u32 frames = 0;

void Game::run()
{
  m_stateManager.registerState<StateStart>(StateID::Start);
  m_stateManager.registerState<StateGame>(StateID::Game);
  m_stateManager.registerState<StateGameOver>(StateID::GameOver);
  m_stateManager.registerState<StateClear>(StateID::Clear);

  m_stateManager.requestStateChange(StateChange::Push, StateID::Start);

  m_running = init();
  f32 lastTime, thisTime, elapsed = 0, accumulator = 0, currentFrames = 0;

  Render::setClearColor(Color::Grey);

  lastTime = Clock::Now();

  while (m_running)
  {
    handleEvents();
    update(elapsed);
    draw();
    thisTime = Clock::Now();
    elapsed = thisTime - lastTime;
    lastTime = thisTime;
    accumulator += elapsed;
    currentFrames++;
    if (accumulator >= 1.f)
    {
      frames = currentFrames;
      currentFrames = 0;
      accumulator = 0;
    }
  }
  quit();
}

void Game::update(f32 const delta)
{
  m_stateManager.update(delta);
}

void Game::draw()
{
  Render::renderBegin();

  m_stateManager.draw();
  if (m_renderFPS)
  {
    Render::drawText({1, 20}, 0x00ff00aa, std::format("FPS:{}", frames));
  }
  Render::renderEnd();
}

} // namespace si
