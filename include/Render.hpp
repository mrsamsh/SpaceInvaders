//
// Render.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 16.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include "Shape.hpp"
#include "Color.hpp"

#include <string_view>
#include <fmt/core.h>

namespace si
{

class Render
{
public:
  static bool init(math::ivec2 windowSize, u32 scale);
  static void quit();
  static void drawRect(math::Rect rect, Color color);
  static void fillRect(math::Rect rect, Color color);
  static void drawText(math::vec2 pos, Color color, std::string_view text);
  static void sprite(math::vec2 pos, Color color, usz index);
  static void renderBegin();
  static void renderEnd();
  static void setClearColor(Color color);
  static void handleResize();

  template <typename ... Args>
  static void drawText(math::vec2 pos, Color color, fmt::format_string<Args...> fmt, Args&& ... args)
  {
    return drawText(pos, color, fmt::format(fmt, std::forward<Args>(args)...));
  }
};

} // namespace si

#endif // RENDER_HPP_
