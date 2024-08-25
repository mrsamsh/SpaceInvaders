//
// SoundPlayer.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 22.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "SoundPlayer.hpp"
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "ResourcePath.hpp"

namespace si
{

static Mix_Chunk* Sounds[static_cast<i32>(SoundEffect::Count)] {0};

void SoundPlayer::init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) != 0)
  {
  }
  Sounds[enm::underlying_v<SoundEffect::Note1>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Sound1.wav"));
  Sounds[enm::underlying_v<SoundEffect::Note2>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Sound2.wav"));
  Sounds[enm::underlying_v<SoundEffect::Note3>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Sound3.wav"));
  Sounds[enm::underlying_v<SoundEffect::Note4>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Sound4.wav"));
  Sounds[enm::underlying_v<SoundEffect::Shoot1>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Shoot1.wav"));
  Sounds[enm::underlying_v<SoundEffect::Shoot2>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Shoot2.wav"));
  Sounds[enm::underlying_v<SoundEffect::Explosion1>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Explosion1.wav"));
  Sounds[enm::underlying_v<SoundEffect::Explosion2>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Explosion2.wav"));
  Sounds[enm::underlying_v<SoundEffect::Mystery>] = Mix_LoadWAV(si::GetResourcePath("Sounds/Mystery.wav"));
  setVolume(SoundChannel::Bullets, 4);
  setVolume(SoundChannel::Explosions, 4);
}

void SoundPlayer::quit()
{
  usz count = enm::underlying_v<SoundEffect::Count>;
  for (usz i = 0; i < count; ++i)
    Mix_FreeChunk(Sounds[i]);
}

void SoundPlayer::setVolume(EnumWrapper<SoundChannel> channel, i32 volume)
{
  Mix_Volume(channel, volume * 12.8);
}

void SoundPlayer::stop(EnumWrapper<SoundChannel> channel)
{
  Mix_HaltChannel(channel);
}

void SoundPlayer::play(EnumWrapper<SoundEffect> sound, i32 repeat)
{
  int channel;
  switch (static_cast<int>(sound))
  {
    case 0:
    case 1:
    case 2:
    case 3:
      channel = enm::getUnderlying(SoundChannel::Music);
    break;
    case 4:
    case 5:
      channel = enm::getUnderlying(SoundChannel::Bullets);
      break;
    case 6:
    case 7:
      channel = enm::getUnderlying(SoundChannel::Explosions);
    break;
    default:
      channel = enm::getUnderlying(SoundChannel::Mystery);
    break;
  }
  Mix_PlayChannel(channel, Sounds[sound], repeat);
}

} // namespace si
