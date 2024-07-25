//
// SoundPlayer.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 22.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "SoundPlayer.hpp"
#include <SDL2/SDL_mixer.h>

namespace si
{

static Mix_Chunk* Sounds[4];

void SoundPlayer::init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
  {
  }
  Sounds[0] = Mix_LoadWAV("resources/Sounds/Sound1.wav");
  Sounds[1] = Mix_LoadWAV("resources/Sounds/Sound2.wav");
  Sounds[2] = Mix_LoadWAV("resources/Sounds/Sound3.wav");
  Sounds[3] = Mix_LoadWAV("resources/Sounds/Sound4.wav");
}

void SoundPlayer::quit()
{
  Mix_FreeChunk(Sounds[0]);
  Mix_FreeChunk(Sounds[1]);
  Mix_FreeChunk(Sounds[2]);
  Mix_FreeChunk(Sounds[3]);
}

} // namespace si
