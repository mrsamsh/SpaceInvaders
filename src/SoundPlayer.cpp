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

namespace si
{

static Mix_Chunk* Sounds[static_cast<i32>(SoundEffect::Count)] {0};

void SoundPlayer::init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) != 0)
  {
  }
  Sounds[underlying(SoundEffect::Note1)] = Mix_LoadWAV("resources/Sounds/Sound1.wav");
  Sounds[underlying(SoundEffect::Note2)] = Mix_LoadWAV("resources/Sounds/Sound2.wav");
  Sounds[underlying(SoundEffect::Note3)] = Mix_LoadWAV("resources/Sounds/Sound3.wav");
  Sounds[underlying(SoundEffect::Note4)] = Mix_LoadWAV("resources/Sounds/Sound4.wav");
  Sounds[underlying(SoundEffect::Shoot1)] = Mix_LoadWAV("resources/Sounds/Shoot1.wav");
  Sounds[underlying(SoundEffect::Shoot2)] = Mix_LoadWAV("resources/Sounds/Shoot2.wav");
  Sounds[underlying(SoundEffect::Explosion1)] = Mix_LoadWAV("resources/Sounds/Explosion1.wav");
  Sounds[underlying(SoundEffect::Explosion2)] = Mix_LoadWAV("resources/Sounds/Explosion2.wav");
  Sounds[underlying(SoundEffect::Mystery)] = Mix_LoadWAV("resources/Sounds/Mystery.wav");
  setVolume(SoundChannel::Bullets, 4);
  setVolume(SoundChannel::Explosions, 4);
}

void SoundPlayer::quit()
{
  usz count = underlying(SoundEffect::Count);
  for (usz i = 0; i < count; ++i)
    Mix_FreeChunk(Sounds[i]);
}

void SoundPlayer::setVolume(Enum<SoundChannel> channel, i32 volume)
{
  Mix_Volume(channel, volume * 12.8);
}

void SoundPlayer::stop(Enum<SoundChannel> channel)
{
  Mix_HaltChannel(channel);
}

void SoundPlayer::play(Enum<SoundEffect> sound, i32 repeat)
{
  int channel;
  switch (static_cast<int>(sound))
  {
    case 0:
    case 1:
    case 2:
    case 3:
      channel = underlying(SoundChannel::Music);
    break;
    case 4:
    case 5:
      channel = underlying(SoundChannel::Bullets);
      break;
    case 6:
    case 7:
      channel = underlying(SoundChannel::Explosions);
    break;
    default:
      channel = underlying(SoundChannel::Mystery);
    break;
  }
  Mix_PlayChannel(channel, Sounds[sound], repeat);
}

} // namespace si
