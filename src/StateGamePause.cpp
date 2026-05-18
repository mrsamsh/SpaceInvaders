//
// StateGamePause.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 09.05.2026.
// Copyright © 2026 Usama Alshughry. All rights reserved.
//

#include "StateGamePause.hpp"
#include "StateManager.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include "GameContext.hpp"

namespace si
{

StateGamePause::StateGamePause(StateManager& manager)
: State(manager, StateID::Pause) { }

bool StateGamePause::update(f32 const delta)
{
  if (Input::isKeyJustPressed(Key::Pause) || Input::isKeyJustReleased(Key::Fire))
  {
    m_manager.requestStateChange(StateChange::Pop);
  }
  return false;
}

void StateGamePause::draw() const
{
  Render::drawText({(GameContext::WindowSize.x - 63) / 2.f, 20.f}, Color::White, "~ PAUSE ~");
}

} // namespace si
