cmake_minimum_required(VERSION 3.23)

project(Variant)

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
  VariantTest
  tests/VariantTest.cpp
)
target_include_directories(VariantTest PRIVATE includes)
target_link_libraries(VariantTest gtest gmock gtest_main)
