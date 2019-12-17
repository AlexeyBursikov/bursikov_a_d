cmake_minimum_required(VERSION 2.8)	
project(another_stack)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_HOME_DIRECTORY}/bin
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#find_package( Boost 1.40 COMPONENTS lockfree REQUIRED)
#include_directories( ${Boost_INCLUDE_DIR} )

set(STACK_HEADERS
    stack.h)
set(STACK_SOURSES
    stack.cpp)

set(TIMER_HEADERS timer.h)
set(TIMER_HEADERS timer.cpp)

add_library(stack
  ${STACK_HEADERS}
  ${STACK_SOURSES})

add_library(timer
  ${TIMER_HEADERS}
  ${TIMER_SOURSES})


add_executable(main main.cpp)
target_link_libraries(main stack timer pthread)

add_executable(test_timer test_timer.cpp)
target_link_libraries(test_timer timer pthread)

add_executable(test_chrono test_chrono.cpp)
target_link_libraries(test_chrono timer pthread)

add_executable(test_stack test_stack.cpp)
target_link_libraries(test_stack timer stack ${GTEST_LIBRARIES} pthread)

add_test(NAME test_stack COMMAND test_stack "./test_stack.cpp")
