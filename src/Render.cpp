//
// Render.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 16.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Render.hpp"
#include <SDL2/SDL.h>
#include "ResourcePath.hpp"
#include <stb/stb_image.h>

namespace si
{

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Texture* texture = nullptr;
static math::ivec2 WindowSize;
static u32 Scale;
static Color clearColor = Color::Black;

namespace priv
{

void setDrawColor(Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

} // namespace priv

bool Render::init(math::ivec2 windowSize, u32 scale)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return false;
  WindowSize = windowSize;
  Scale = scale;
  window = SDL_CreateWindow(
        "Space Invaders",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WindowSize.x * Scale,
        WindowSize.y * Scale,
        SDL_WINDOW_SHOWN
      );
  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED
      // | SDL_RENDERER_PRESENTVSYNC
  );
  SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
  if (window == nullptr || renderer == nullptr)
    return false;

  // load texture
  int w = 0, h = 0, nc = 0;
  u8 * rawImage = stbi_load(GetResourcePath("Sprites.png"), &w, &h, &nc, 0);
  SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
    rawImage,
    w, h,
    sizeof(u8) * nc, sizeof(u8) * nc * w,
    SDL_PIXELFORMAT_RGBA32
  );
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(surface);
  stbi_image_free(rawImage);

  return true;
}

void Render::quit()
{
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

void Render::setClearColor(Color color)
{
  clearColor = color;
}

void Render::renderBegin()
{
  priv::setDrawColor(clearColor);
  SDL_RenderClear(renderer);
  priv::setDrawColor(Color::White);
}

void Render::renderEnd()
{
  SDL_RenderPresent(renderer);
}

void Render::drawRect(math::Rect rect, Color color)
{
  rect.position *= Scale;
  rect.size *= Scale;
  SDL_FRect srect{rect.x, rect.y, rect.w, rect.h};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRectF(renderer, &srect);
}

void Render::fillRect(math::Rect rect, Color color)
{
  rect.position *= Scale;
  rect.size *= Scale;
  SDL_FRect srect{rect.x, rect.y, rect.w, rect.h};
  priv::setDrawColor(color);
  SDL_RenderFillRectF(renderer, &srect);
}

void Render::drawText(math::vec2 pos, Color color, std::string_view text)
{
  pos *= Scale;
  static constexpr f32 spacing = 7.f;
  SDL_Rect src{0, 64, 8, 8};
  SDL_FRect dst{pos.x, pos.y, 8.f * Scale, 8.f * Scale};
  priv::setDrawColor(color);
  for (char const& c : text)
  {
    auto i = static_cast<size_t>(c);
    i32 x = (i % 16) * 8;
    i32 y = (i / 16) * 8;
    SDL_Rect currentSrc{src.x + x, src.y + y, src.w, src.h};
    SDL_RenderCopyF(
        renderer,
        texture,
        &currentSrc,
        &dst
        );
    dst.x += spacing * Scale;
    if (c >= 'a' && c <= 'z')
      dst.x--;
  }
}

void Render::sprite(math::vec2 pos, Color color, usz index)
{
  int x = (index % 8) * 16;
  int y = (index / 8) * 16;
  SDL_Rect src{x, y, 16, 16};
  SDL_FRect dst{pos.x * Scale, pos.y * Scale, 16.f * Scale, 16.f * Scale};
  priv::setDrawColor(color);
  SDL_RenderCopyF(
      renderer,
      texture,
      &src,
      &dst
  );
}

void Render::handleResize()
{

}

} // namespace si
