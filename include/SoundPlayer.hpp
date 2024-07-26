//
// SoundPlayer.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 22.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef SOUNDPLAYER_HPP_
#define SOUNDPLAYER_HPP_

#include "MyTypes.hpp"
#include "Enum.hpp"

namespace si
{

enum class SoundEffect
{
  Note1 = 0,
  Note2,
  Note3,
  Note4,
  Shoot1,
  Shoot2,
  Explosion1,
  Explosion2,
  Count
};

class SoundPlayer
{
public:
  static void init();
  static void play(Enum<SoundEffect> effect);
  static void quit();
};

} // namespace si

#endif // SOUNDPLAYER_HPP_
