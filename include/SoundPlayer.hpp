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

namespace si
{

enum class SoundEffect
{
  
};

class SoundPlayer
{
public:
  static void init();
  static void playSoundEffect(SoundEffect effect);
  static void quit();
};

} // namespace si

#endif // SOUNDPLAYER_HPP_
