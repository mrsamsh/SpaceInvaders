cmake_minimum_required(VERSION 3.20)

# files to compile for library
add_library(math STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Rand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MathConcepts.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MathHelper.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MyTypes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Rand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Vector.hpp
)

# include directory
target_include_directories(math
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(math
  PRIVATE
    cxx_std_20
)

add_executable(vector_test #EXCLUDE_FROM_ALL
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/VectorTest.cpp
)

target_compile_features(vector_test
  PRIVATE
    cxx_std_20
)

target_include_directories(vector_test
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_test(
  NAME TestVector
  COMMAND $<TARGET_FILE:vector_test>
)
