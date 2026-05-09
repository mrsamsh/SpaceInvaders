//
// GameContext.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 26.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef GAMECONTEXT_HPP_
#define GAMECONTEXT_HPP_

#include "MyTypes.hpp"
#include "Vector.hpp"

namespace si
{

struct GameContext
{
  static constexpr f32 Delta = 1.0f / 60.0f;
  static constexpr math::ivec2 WindowSize{240, 180};
  static u32 HighScore;
  static bool NewHighScore;
  static bool UseFx;
  static bool EasyMode;
};

} // namespace si

#endif // GAMECONTEXT_HPP_
