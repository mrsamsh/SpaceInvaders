//
// StateGameOver.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 14.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateGameOver.hpp"
#include "Game.hpp"
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
    Game::NewHighScore = false;
  }
  return false;
}

void StateGameOver::draw() const
{
  Render::fillRect({0, 0, 240, 200}, Color(10, 0, 0, 120));
  Render::drawText({92, 85}, Color::White, "GAME OVER");
  if (Game::NewHighScore)
  {
    Render::drawText({68, 100}, Color::Red, "NEW HIGH SCORE!");
    Render::drawText({103, 112}, Color::Red, std::format("{:05}", Game::HighScore));
  }
}

} // namespace si
