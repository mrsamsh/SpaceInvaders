cmake_minimum_required(VERSION 3.20)

project(SpaceInvadors)

find_package(SDL2 REQUIRED )
find_package(SDL2_image REQUIRED )

set(USE_OPENGL OFF CACHE BOOL "")

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/Math)

if (USE_OPENGL)
  add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glad)
  add_subdirectory(${CMAKE_SOURCE_DIR}/libs/stb)
endif()

# compile commands for clangd
mark_as_advanced(CLEAR CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

set(SourceFiles
  src/main.cpp
  src/Game.cpp
  src/Color.cpp
  src/Clock.cpp
  src/GameInternal.cpp
  src/Player.cpp
  src/Enemy.cpp
  src/Bullets.cpp
  src/Sandbag.cpp
  src/Explosion.cpp
  src/MysteryShip.cpp
  src/StateManager.cpp
  src/StateGame.cpp
  src/StateStart.cpp
  src/StateClear.cpp
  src/StateGameOver.cpp
  src/Input.cpp
)

set (Libraries 
  SDL2::SDL2
  SDL2_image
  math
)

if (USE_OPENGL)
  set (Libraries ${Libraries} glad stb_image)
endif()

if (USE_OPENGL)
  set (SourceFiles ${SourceFiles} src/RenderOpenGL.cpp)
else()
  set (SourceFiles ${SourceFiles} src/Render.cpp)
endif()

# files to compile for executable
add_executable(app
  ${SourceFiles}
)

target_link_libraries(app
  PRIVATE
    ${Libraries}
)

# include directory
target_include_directories(app
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(app
  PRIVATE
    cxx_generalized_initializers
    cxx_relaxed_constexpr
    cxx_std_20
)

add_custom_command(
  TARGET app POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E create_symlink
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
  DEPENDS "${CMAKE_SOURCE_DIR}/compile_commands.json"
  COMMENT "Creating symlink for compile_commands"
)

