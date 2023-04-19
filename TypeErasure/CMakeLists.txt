cmake_minimum_required(VERSION 3.23)

project(TypeErasure)

include(FetchContent)

set (CMAKE_CXX_STANDARD 14)

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
  WrapperTest
  tests/WrapperTest.cpp
)
target_include_directories(WrapperTest PRIVATE includes)
target_link_libraries(WrapperTest gtest gmock gtest_main)
