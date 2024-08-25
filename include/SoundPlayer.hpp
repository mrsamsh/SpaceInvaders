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
#include "EnumWrapper.hpp"

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
  Mystery,
  Count
};

enum class SoundChannel
{
  Music,
  Bullets,
  Explosions,
  Mystery,
  Count
};

class SoundPlayer
{
public:
  static void init();
  static void play(EnumWrapper<SoundEffect> effect, i32 repeat = 0);
  static void setVolume(EnumWrapper<SoundChannel> channel, i32 volume);
  static void stop(EnumWrapper<SoundChannel> channel);
  static void quit();
};

} // namespace si

#endif // SOUNDPLAYER_HPP_
