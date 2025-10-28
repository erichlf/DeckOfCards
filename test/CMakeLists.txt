find_package(GTest 1.8 REQUIRED)
find_package(Boost REQUIRED)  # math is a header only so don't use COMPONENT

add_executable(DeckTest DeckTest.cpp)
target_include_directories(DeckTest PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(DeckTest DeckOfCards GTest::GTest GTest::Main -no-pie)
gtest_add_tests(TARGET DeckTest)
