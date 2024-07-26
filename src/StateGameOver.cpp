//
// StateGameOver.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 14.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateGameOver.hpp"
#include "GameContext.hpp"
#include "StateManager.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include <format>

namespace si
{

StateGameOver::StateGameOver(StateManager& manager)
: State(manager, StateID::GameOver) { }

bool StateGameOver::update(f32 const delta)
{
  m_accumulator += delta;
  if (Input::isKeyJustPressed(Key::Fire) || m_accumulator > 5.f)
  {
    m_manager.requestStateChange(StateChange::Clear);
    m_manager.requestStateChange(StateChange::Push, StateID::Start);
    GameContext::NewHighScore = false;
  }
  return false;
}

void StateGameOver::draw() const
{
  Render::fillRect({0, 0, GameContext::WindowSize.x, GameContext::WindowSize.y}, Color(10, 0, 0, 120));
  Render::drawText({(GameContext::WindowSize.x - 63) / 2.f, 85}, Color::White, "GAME OVER");
  if (GameContext::NewHighScore)
  {
    Render::drawText({(GameContext::WindowSize.x -105) / 2.f, 100}, Color::Red, "NEW HIGH SCORE!");
    Render::drawText({(GameContext::WindowSize.x - 35) / 2.f, 112}, Color::Red, std::format("{:05}", GameContext::HighScore));
  }
}

} // namespace si
