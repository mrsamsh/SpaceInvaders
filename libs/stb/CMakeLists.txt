cmake_minimum_required(VERSION 3.20)

project(STB_Image)

add_library(stb_image INTERFACE)

target_include_directories(stb_image
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(stb_image
  INTERFACE
    STB_IMAGE_IMPLEMENTATION
)
