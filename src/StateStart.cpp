//
// StateStart.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateStart.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Render.hpp"
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
  Render::drawText({70.50, 33.50}, Color::Blue, "SPACE INVADERS");
  Render::drawText({71, 34}, Color::White, "SPACE INVADERS");

  Render::sprite({70, 66}, Color::Red, 24);
  Render::drawText({94, 70}, Color::White, "= ?? POINTS");
  Render::sprite({70, 80}, Color::White, 0);
  Render::drawText({94, 84}, Color::White, "= 30 POINTS");
  Render::sprite({70, 94}, Color::Yellow, 8);
  Render::drawText({94, 98}, Color::White, "= 20 POINTS");
  Render::sprite({70, 108}, Color::Blue, 16);
  Render::drawText({94, 112}, Color::White, "= 10 POINTS");
  Render::drawText({64, 134}, Color::White, "PRESS J TO START");
  Render::drawText({67, 154}, Color::White, "A AND D TO MOVE");
  Render::drawText({67, 164}, Color::White, "  J TO SHOOT   ");
  Render::drawText({28, 184}, Color::Yellow, "programmed by usama alshughry");
}

} // namespace si
