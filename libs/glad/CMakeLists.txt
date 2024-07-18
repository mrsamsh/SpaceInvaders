cmake_minimum_required(VERSION 3.20)

project(GLAD)

add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
)

target_include_directories(glad
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
