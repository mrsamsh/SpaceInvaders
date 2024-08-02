cmake_minimum_required(VERSION 3.20)

project(SpaceInvadors)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_library(FOUNDATION Foundation REQUIRED)

# set(OSX_10_11_SDK_PATH /Users/usama/Downloads/MacOSX10.11.sdk)
# set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)
# set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(USE_OPENGL OFF CACHE BOOL "")
set(USE_OPENGL_FX OFF CACHE BOOL "")


add_subdirectory(${CMAKE_SOURCE_DIR}/libs/Math)

if (USE_OPENGL)
  add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glad)
  add_subdirectory(${CMAKE_SOURCE_DIR}/libs/stb)
endif()

# compile commands for clangd
mark_as_advanced(CLEAR CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

function(resource VAR SOURCE_PATH DESTINATION PATTERN)
    file(GLOB_RECURSE _LIST CONFIGURE_DEPENDS ${SOURCE_PATH}/${PATTERN})
    foreach (RESOURCE ${_LIST})
        get_filename_component(_PARENT ${RESOURCE} DIRECTORY)
        if (${_PARENT} STREQUAL ${SOURCE_PATH})
            set(_DESTINATION ${DESTINATION})
        else ()
            file(RELATIVE_PATH _DESTINATION ${SOURCE_PATH} ${_PARENT})
            set(_DESTINATION ${DESTINATION}/${_DESTINATION})
        endif ()
        set_property(SOURCE ${RESOURCE} PROPERTY MACOSX_PACKAGE_LOCATION ${_DESTINATION})
    endforeach (RESOURCE)
    set(${VAR} ${_LIST} PARENT_SCOPE)
endfunction()

set(SourceFiles
  src/main.cpp
  src/Game.cpp
  src/Color.cpp
  src/Clock.cpp
  src/GameInternal.cpp
  src/GameContext.cpp
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
  src/SoundPlayer.cpp
  src/ResourcePath.mm
)

set (Libraries 
  SDL2::SDL2
  SDL2_image
  SDL2_mixer
  math
  ${FOUNDATION}
)

if (USE_OPENGL)
  set (Libraries ${Libraries} glad stb_image)
endif()

if (USE_OPENGL)
  set (SourceFiles ${SourceFiles} src/RenderOpenGL.cpp)
else()
  set (SourceFiles ${SourceFiles} src/Render.cpp)
endif()

resource(ALL_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Resources Resources *)

set(RESOURCE_FILES ${ALL_RESOURCES})

# files to compile for executable
add_executable(SpaceInvaders MACOSX_BUNDLE
  ${SourceFiles}
  ${RESOURCE_FILES}
)

set_target_properties(SpaceInvaders
PROPERTIES
  MACOSX_BUNDLE_NAME            "SpaceInvaders"
  MACOSX_BUNDLE_VERSION         "1.0"
  MACOSX_BUNDLE_GUI_IDENTIFIER  "com.mrsamsh.si"
  MACOSX_BUNDLE_ICON_FILE       "icon.icns"
  MACOSX_BUNDLE   "TRUE"
)

if (USE_OPENGL AND USE_OPENGL_FX)
  target_compile_definitions(SpaceInvaders
    PRIVATE
      USE_EFFECT
    )
endif()

target_link_libraries(SpaceInvaders
  PRIVATE
    ${Libraries}
)

# include directory
target_include_directories(SpaceInvaders
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(SpaceInvaders
  PRIVATE
    cxx_generalized_initializers
    cxx_relaxed_constexpr
    cxx_std_20
)

# target_compile_options(SpaceInvaders
#   PUBLIC
#     -mmacosx-version-min=10.9 -arch x86_64
# )

add_custom_command(
  TARGET SpaceInvaders POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E create_symlink
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
  DEPENDS "${CMAKE_SOURCE_DIR}/compile_commands.json"
  COMMENT "Creating symlink for compile_commands"
)

