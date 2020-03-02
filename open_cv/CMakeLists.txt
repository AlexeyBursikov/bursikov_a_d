cmake_minimum_required(VERSION 3.0)

project(cv)

set(OpenCV_DIR F:/opt/OpenCV/opencv/build)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(hw0)
add_subdirectory(hw1)
add_subdirectory(hw2)