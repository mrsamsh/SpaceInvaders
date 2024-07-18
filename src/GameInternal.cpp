//
// GameInternal.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 07.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include "Input.hpp"
#include "Render.hpp"

namespace si
{

bool Game::init()
{
  m_windowSize.x = 240;
  m_windowSize.y = 200;
  bool result = Render::init(m_windowSize, Scale);
  Input::init();
  return result;
}

void Game::quit()
{
  Render::quit();
}

void Game::handleEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_WINDOWEVENT:
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          m_resized = true;
          break;
        default:
          break;
        }
        break;
      case SDL_QUIT:
        m_running = false;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            m_running = false;
            break;
          case SDLK_p:
            if (event.key.repeat == 0)
              m_renderFPS = !m_renderFPS;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  if (m_resized) handleResize();
  Input::updateInput();
}

void Game::handleResize()
{
  m_resized = false;
  Render::handleResize();
}

} // namespace si
