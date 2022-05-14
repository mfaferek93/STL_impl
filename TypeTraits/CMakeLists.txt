cmake_minimum_required(VERSION 3.23)

project(TypeTraits)

include(FetchContent)

set (CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

add_executable(
  TypeTraitsTest
  tests/TypeTraitsTest.cpp
)
target_include_directories(TypeTraitsTest PRIVATE includes)
target_link_libraries(TypeTraitsTest gtest gmock gtest_main)
