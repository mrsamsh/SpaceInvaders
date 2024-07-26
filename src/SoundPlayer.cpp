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
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
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
}

void SoundPlayer::quit()
{
  usz count = underlying(SoundEffect::Count);
  for (usz i = 0; i < count; ++i)
    Mix_FreeChunk(Sounds[i]);
}

void SoundPlayer::play(Enum<SoundEffect> sound)
{
  Mix_PlayChannel(-1, Sounds[sound], 0);
}

} // namespace si
