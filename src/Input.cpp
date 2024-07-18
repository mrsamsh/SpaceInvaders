//
// Input.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 16.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Input.hpp"

#include <SDL2/SDL.h>

namespace si
{

u8 const* Input::Keyboard = nullptr;
Key Input::m_keys[3];

void Input::init()
{
  Input::Keyboard = SDL_GetKeyboardState(nullptr);
  m_keys[Key::Left].code = SDL_SCANCODE_A;
  m_keys[Key::Right].code = SDL_SCANCODE_D;
  m_keys[Key::Fire].code = SDL_SCANCODE_J;
}

void Input::updateInput()
{
  for (int i = 0; i < 3; ++i)
  {
    m_keys[i].lastTime = m_keys[i].thisTime;
    m_keys[i].thisTime = Keyboard[m_keys[i].code];
  }
}

bool Input::isKeyPressed(Key::Code code)
{
  return m_keys[code].thisTime;
}

bool Input::isKeyJustPressed(Key::Code code)
{
  return m_keys[code].thisTime && !m_keys[code].lastTime;
}

bool Input::isKeyReleased(Key::Code code)
{
  return !m_keys[code].thisTime;
}

bool Input::isKeyJustReleased(Key::Code code)
{
  return !m_keys[code].thisTime && m_keys[code].lastTime;
}

} // namespace si
