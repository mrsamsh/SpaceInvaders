//
// StateStart.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateStart.hpp"
#include "Input.hpp"
#include "Render.hpp"
#include "StateManager.hpp"
#include <iostream>

namespace si
{


StateStart::StateStart(StateManager& manager)
: State{manager, StateID::Start}
{

}

bool StateStart::update(f32 const delta)
{
  if (Input::isKeyJustPressed(Key::Fire))
  {
    m_manager.requestStateChange(StateChange::Pop);
    m_manager.requestStateChange(StateChange::Push, StateID::Game);
  }
  return false;
}

void StateStart::draw() const
{
  Render::drawText({70.50, 29.50}, Color::Blue, "SPACE INVADERS");
  Render::drawText({71, 30}, Color::White, "SPACE INVADERS");

  Render::sprite({70, 49}, Color::Red, 24);
  Render::drawText({94, 54}, Color::White, "= ?? POINTS");
  Render::sprite({70, 64}, Color::White, 0);
  Render::drawText({94, 68}, Color::White, "= 30 POINTS");
  Render::sprite({70, 78}, Color::Yellow, 8);
  Render::drawText({94, 82}, Color::White, "= 20 POINTS");
  Render::sprite({70, 92}, Color::Blue, 16);
  Render::drawText({94, 96}, Color::White, "= 10 POINTS");
  Render::drawText({50, 118}, Color::White, "PRESS SPACE TO START");
  Render::drawText({28, 164}, Color::Yellow, "programmed by usama alshughry");
}

} // namespace si
