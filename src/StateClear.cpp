//
// StateClear.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateClear.hpp"
#include "StateManager.hpp"
#include "Game.hpp"
#include "Render.hpp"

namespace si
{


StateClear::StateClear(StateManager& manager)
: State(manager, StateID::Clear)
, m_accumulator{0.f}
{ }

bool StateClear::update(f32 const delta)
{
  m_accumulator += delta;
  if (m_accumulator >= 3)
  {
    m_manager.requestStateChange(StateChange::Pop);
  }
  return false;
}

void StateClear::draw() const
{
  Render::fillRect({44, 68, 152, 64}, 0x00000099);
  Render::drawText({82, 94}, Color::White, "LEVEL CLEAR");
}

} // namespace si
