//
// RenderOpenGL.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 16.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Render.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

namespace si
{
// variables

struct VertexAttribs
{
  math::vec2 translation;
  Color color;
  float spriteIndex;
};

struct RectAttribs
{
  math::vec2 translation;
  math::vec2 scale;
  Color color;
};

static SDL_Window* window = nullptr;
static GLuint program;
static GLuint rectProgram;
static GLuint texture;
static GLuint vaoSprite, vboSprites, vboSpriteAttribs;
static GLuint vaoText,   vboText,    vboTextAttribs;
static GLuint vaoRect,   vboRect,    vboRectAttribs;
static constexpr usz MaxQuads = 2000;
static math::vec4T<float> clearColor;
static math::vec4T<float> drawColor;
static std::vector<VertexAttribs> spriteAttribs;
static std::vector<VertexAttribs> textAttribs;
static std::vector<RectAttribs>   rectAttribs;

static char const* vertRectShaderSource = R"(
#version 410 core

uniform mat4 projection;

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTranslation;
layout (location = 2) in vec2 aScale;
layout (location = 3) in vec4 aColor;

out vec4 Color;

void main()
{
  vec2 pos = aPosition * aScale + aTranslation;
  gl_Position = projection * vec4(pos, 0, 1);

  Color = aColor;
}
)";

static char const* fragRectSource = R"(
#version 410 core

in vec4 Color;

out vec4 FragColor;

void main()
{
  FragColor = Color;
}
)";

static char const* vertShaderSource = R"(
#version 410 core

uniform mat4 projection;

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec2 aTranslation;
layout (location = 3) in vec4 aColor;
layout (location = 4) in float aSpriteIndex;

out vec2 TexCoords;
out vec4 Color;

void main()
{
  vec2 translatedPosition = vec2(
    floor(aTranslation.x + aPosition.x),
    floor(aTranslation.y + aPosition.y)
  );

  ivec2 GridSize;
  vec2 SpriteSize;
  if (aSpriteIndex < 100)
  {
    GridSize = ivec2(8, 8);
    SpriteSize = vec2(1.0 / GridSize.x, 1.0 / GridSize.y);
  }
  else
  {
    GridSize = ivec2(16, 16);
    SpriteSize = vec2(0.046875, 0.0625);
  }

  int xx = int(aSpriteIndex) % GridSize.x;
  int yy = int(aSpriteIndex) / GridSize.y;

  TexCoords = vec2(
    aTexCoords.x + xx * SpriteSize.x,
    aTexCoords.y + yy * SpriteSize.y
  );

  gl_Position = projection * vec4(translatedPosition, 0.0, 1.0);
  Color = aColor;
}
)";

static char const* fragShaderSource = R"(
#version 410 core

uniform sampler2D SpritesTexture;

// int PixelSide = 4;

in vec4 Color;
in vec2 TexCoords;
out vec4 FragColor;

void main()
{
  // vec2 modval = vec2(
  //   mod(gl_FragCoord.x, PixelSide),
  //   mod(gl_FragCoord.y, PixelSide)
  // );

  // if (modval.x < 1 || modval.x > PixelSide - 1)
  //   FragColor = texture(SpritesTexture, TexCoords) * Color * vec4(1.0, 1.0, 1.0, 0.4);
  // else
  // if (modval.y < 1 || modval.y > PixelSide - 1)
  //   FragColor = texture(SpritesTexture, TexCoords) * Color * vec4(1.0, 1.0, 1.0, 0.4);
  // else
    FragColor = texture(SpritesTexture, TexCoords) * Color;
}
)";

// helper functions declerations
GLuint loadShader(GLenum type, char const* source);
GLuint loadProgram(GLuint vs, GLuint fs);
void initDrawObjects();
GLuint loadTexture(std::string_view filename);
std::array<float, 16> ortho(float left, float right, float top, float bottom, float near, float far);

bool Render::init(math::ivec2 windowSize, u32 scale)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    return false;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow(
      "Space Invaders",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      windowSize.x * scale,
      windowSize.y * scale,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
      );

  if (window == nullptr)
    return false;

  SDL_GL_CreateContext(window);

  if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
    return false;
  printf("GL Loaded!\n");
  printf("Version:    %s\n", glGetString(GL_VERSION));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto vs = loadShader(GL_VERTEX_SHADER, vertShaderSource);
  auto fs = loadShader(GL_FRAGMENT_SHADER, fragShaderSource);

  program = loadProgram(vs, fs);
  glUseProgram(program);
  auto projection = ortho(0, 240, 0, 200, -100, 100);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false,
      projection.data());

  glDeleteShader(vs);
  glDeleteShader(fs);

  vs = loadShader(GL_VERTEX_SHADER, vertRectShaderSource);
  fs = loadShader(GL_FRAGMENT_SHADER, fragRectSource);
  rectProgram = loadProgram(vs, fs);
  glUseProgram(rectProgram);
  glUniformMatrix4fv(glGetUniformLocation(rectProgram, "projection"), 1, false,
      projection.data());

  glDeleteShader(vs);
  glDeleteShader(fs);

  texture = loadTexture("resources/Sprites.png");

  initDrawObjects();

  spriteAttribs.reserve(MaxQuads);
  textAttribs.reserve(MaxQuads);
  rectAttribs.reserve(MaxQuads);

  return true;
}

void Render::quit()
{
  if (window)
  {
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
}

void Render::drawRect(math::Rect rect, Color color)
{

}

void Render::fillRect(math::Rect rect, Color color)
{
  rectAttribs.push_back({
      rect.position,
      rect.size,
      color
      });
}

void Render::drawText(math::vec2 pos, Color color, std::string_view text)
{
  static constexpr f32 spacing = 7.f;
  for (char const& c : text)
  {
    float i = static_cast<usz>(c) + 128.f;
    textAttribs.push_back({
          // position
          pos,
          // color,
          color,
          // sprite,
          i
        });
    pos.x += spacing;
    if (c >= 'a' && c <= 'z')
      pos.x--;
  }
}

void Render::sprite(math::vec2 pos, Color color, usz index)
{
  spriteAttribs.push_back({pos, color, static_cast<float>(index)});
}

void Render::renderBegin()
{
  glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::renderEnd()
{
  glUseProgram(rectProgram);
  glBindVertexArray(vaoRect);
  glBindBuffer(GL_ARRAY_BUFFER, vboRectAttribs);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(RectAttribs) * rectAttribs.size(),
      rectAttribs.data());
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, rectAttribs.size());
  rectAttribs.clear();

  glUseProgram(program);
  glBindVertexArray(vaoSprite);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindBuffer(GL_ARRAY_BUFFER, vboSpriteAttribs);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribs) * spriteAttribs.size(),
      spriteAttribs.data());
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, spriteAttribs.size());
  spriteAttribs.clear();

  glBindVertexArray(vaoText);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindBuffer(GL_ARRAY_BUFFER, vboTextAttribs);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexAttribs) * textAttribs.size(),
      textAttribs.data());
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, textAttribs.size());
  textAttribs.clear();

  SDL_GL_SwapWindow(window);
}

void Render::setClearColor(Color color)
{
  clearColor = color.normalized();
}

void Render::handleResize()
{
  int width, height;
  float ratio = 240.f / 200.f;
  SDL_GetWindowSize(window, &width, &height);
  int offsetx = 0, offsety = 0;
  float fwidth = float(width), fheight = float(height);
  if (fwidth / fheight < ratio)
  {
    int ww = width;
    width = 240 * (width / 240);
    fheight = width / ratio;
    offsety = (height - fheight) / 2;
    offsetx = (ww - width) / 2;
    height = fheight;
  }
  else
  {
    int hh = height;
    height = 200 * (height / 200);
    fwidth = height * ratio;
    offsetx = (width - fwidth) / 2;
    offsety = (hh - height) / 2;
    width = fwidth;
  }
  // SDL_SetWindowSize(window, width, height);
  glViewport(offsetx, offsety, width, height);
}

GLuint loadShader(GLenum type, char const* source)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == 0)
  {
    char buffer[512] = {0};
    glGetShaderInfoLog(shader, 512, nullptr, buffer);
    printf("Failed to load shader: %s\n", buffer);
  }
  return shader;
}

GLuint loadProgram(GLuint vs, GLuint fs)
{
  GLuint p = glCreateProgram();
  glAttachShader(p, vs);
  glAttachShader(p, fs);
  glLinkProgram(p);
  int success;
  glGetProgramiv(p, GL_LINK_STATUS, &success);
  if (success == 0)
  {
    char buffer[512] = {0};
    glGetProgramInfoLog(p, 512, nullptr, buffer);
    printf("Error linking program: %s\n", buffer);
  }
  return p;
}

struct Vertex
{
  math::vec2 position;
  math::vec2 texCoords;
};

#define OFFSETOF(t, d) (void*)offsetof(t, d)

void initDrawObjects()
{
  Vertex spriteVertices[]
  {
    {{ 0.f,  0.f}, {   0.f, 0.f   }},
    {{16.f,  0.f}, {0.125f, 0.f   }},
    {{16.f, 16.f}, {0.125f, 0.125f}},
    {{ 0.f,  0.f}, {   0.f, 0.f   }},
    {{16.f, 16.f}, {0.125f, 0.125f}},
    {{ 0.f, 16.f}, {   0.f, 0.125f}}
  };

  Vertex textVertices[]
  {
    // 8 * 6        0.0625 * 0.046875
    {{ 0.f,  0.f}, {      0.f, 0.f    }},
    {{ 6.f,  0.f}, {0.046875f, 0.f    }},
    {{ 6.f,  8.f}, {0.046875f, 0.0625f}},
    {{ 0.f,  0.f}, {      0.f, 0.f    }},
    {{ 6.f,  8.f}, {0.046875f, 0.0625f}},
    {{ 0.f,  8.f}, {      0.f, 0.0625f}}
  };

  float rectVertices[]
  {
    0.f, 0.f,
    1.f, 0.f,
    1.f, 1.f,
    0.f, 0.f,
    1.f, 1.f,
    0.f, 1.f
  };

  glGenVertexArrays(1, &vaoSprite);
  glBindVertexArray(vaoSprite);

  glGenBuffers(1, &vboSprites);
  glBindBuffer(GL_ARRAY_BUFFER, vboSprites);
  glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), OFFSETOF(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), OFFSETOF(Vertex, texCoords));

  glGenBuffers(1, &vboSpriteAttribs);
  glBindBuffer(GL_ARRAY_BUFFER, vboSpriteAttribs);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribs) * MaxQuads, nullptr,
      GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, translation));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, color));
  glVertexAttribDivisor(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 1, GL_FLOAT, false, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, spriteIndex));
  glVertexAttribDivisor(4, 1);

  glBindVertexArray(0);

  glGenVertexArrays(1, &vaoText);
  glBindVertexArray(vaoText);

  glGenBuffers(1, &vboText);
  glBindBuffer(GL_ARRAY_BUFFER, vboText);
  glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), textVertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), OFFSETOF(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), OFFSETOF(Vertex, texCoords));

  glGenBuffers(1, &vboTextAttribs);
  glBindBuffer(GL_ARRAY_BUFFER, vboTextAttribs);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribs) * MaxQuads, nullptr,
      GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, translation));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, color));
  glVertexAttribDivisor(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 1, GL_FLOAT, false, sizeof(VertexAttribs),
      OFFSETOF(VertexAttribs, spriteIndex));
  glVertexAttribDivisor(4, 1);

  glBindVertexArray(0);

  glGenVertexArrays(1, &vaoRect);
  glBindVertexArray(vaoRect);

  glGenBuffers(1, &vboRect);
  glBindBuffer(GL_ARRAY_BUFFER, vboRect);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices,
      GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

  glGenBuffers(1, &vboRectAttribs);
  glBindBuffer(GL_ARRAY_BUFFER, vboRectAttribs);
  glBufferData(GL_ARRAY_BUFFER, sizeof(RectAttribs) * MaxQuads, nullptr,
      GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(RectAttribs),
      OFFSETOF(RectAttribs, translation));
  glVertexAttribDivisor(1, 1);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(RectAttribs),
      OFFSETOF(RectAttribs, scale));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, true, sizeof(RectAttribs),
      OFFSETOF(RectAttribs, color));
  glVertexAttribDivisor(3, 1);

  glBindVertexArray(0);
}

#undef OFFSETOF

GLuint loadTexture(std::string_view filename)
{
  GLuint texture;
  int width, height, nrChannels;
  unsigned char* file = stbi_load(filename.data(), &width, &height, &nrChannels, 0);
  if (file == nullptr)
  {
    printf("Failed to load texture %s\n", filename.data());
    return texture;
  }
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, file);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(file);
  return texture;
}

std::array<float, 16> ortho(float l, float r, float t, float b, float n, float f)
{
  std::array<float, 16> m{0};
  m[0]  =   2.f  / (r-l);
  m[5]  =   2.f  / (t-b);
  m[10] = - 2.f  / (f-n);
  m[12] = -(r+l) / (r-l);
  m[13] = -(t+b) / (t-b);
  m[14] = -(f+n) / (f-n);
  m[15] = 1.f;
  return m;
}

} // namespace si
