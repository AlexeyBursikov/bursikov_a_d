cmake_minimum_required(VERSION 2.8)	
project(another_stack)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_HOME_DIRECTORY}/bin
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(STACK_HEADERS stack.h)
set(STACK_SOURSES stack.cpp)

add_library(stack
  ${STACK_HEADERS}
  ${STACK_SOURSES})

add_executable(main main.cpp)
target_link_libraries(main stack)

add_executable(test_stack test_stack.cpp)
target_link_libraries(test_stack stack ${GTEST_LIBRARIES} pthread)

add_test(NAME test_stack COMMAND test_stack "./test_stack.cpp")
