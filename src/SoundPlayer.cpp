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

static Mix_Chunk* Sounds[static_cast<i32>(SoundEffect::Count)];

template <SoundEffect Effect>
static constexpr i32 to_int = static_cast<i32>(Effect);

static constexpr inline i32 toInt(SoundEffect effect)
{
  return static_cast<i32>(effect);
}

void SoundPlayer::init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
  {
  }
  Sounds[to_int<SoundEffect::Note1>] = Mix_LoadWAV("resources/Sounds/Sound1.wav");
  Sounds[to_int<SoundEffect::Note2>] = Mix_LoadWAV("resources/Sounds/Sound2.wav");
  Sounds[to_int<SoundEffect::Note3>] = Mix_LoadWAV("resources/Sounds/Sound3.wav");
  Sounds[to_int<SoundEffect::Note4>] = Mix_LoadWAV("resources/Sounds/Sound4.wav");
  Sounds[to_int<SoundEffect::Shoot1>] = Mix_LoadWAV("resources/Sounds/Shoot1.wav");
  Sounds[to_int<SoundEffect::Explosion1>] = Mix_LoadWAV("resources/Sounds/Explosion1.wav");
  Sounds[to_int<SoundEffect::Explosion2>] = Mix_LoadWAV("resources/Sounds/Explosion2.wav");
}

void SoundPlayer::quit()
{
  usz count = toInt(SoundEffect::Count);
  for (usz i = 0; i < count; ++i)
    Mix_FreeChunk(Sounds[i]);
}

void SoundPlayer::play(SoundEffect sound)
{
  Mix_PlayChannel(-1, Sounds[toInt(sound)], 0);
}

} // namespace si
