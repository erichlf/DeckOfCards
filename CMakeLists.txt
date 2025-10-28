cmake_minimum_required(VERSION 3.6.0)

project(DeckOfCards VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(DeckOfCards
  SHARED
    src/Deck.cpp
)

target_include_directories(DeckOfCards
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(DeckOfCards
  PROPERTIES
    CXX_STANDARD 11
)

find_package(GTest 1.8)

if((TARGET GTest::GTest) AND (TARGET GTest::Main))
  include(CTest)
endif()

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
