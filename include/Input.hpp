//
// Input.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 16.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <SDL2/SDL_keycode.h>
#include "MyTypes.hpp"

namespace si
{

struct Key
{
  enum Code {
    Left  = 0,
    Right,
    Fire,
  };
  SDL_Scancode code;
  bool lastTime, thisTime;
};

class Input
{
public:
  static u8 const* Keyboard;
  static void init();
  static bool isKeyPressed(Key::Code code);
  static bool isKeyJustPressed(Key::Code code);
  static bool isKeyReleased(Key::Code code);
  static bool isKeyJustReleased(Key::Code code);
  static void updateInput();
private:
  static Key m_keys[3];
};

} // namespace si

#endif // INPUT_HPP_
