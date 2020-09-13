cmake_minimum_required(VERSION 3.13)

project(PopColor VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories( src/utilities )
set( SRC_LIST src/main.cpp src/utilities/rgb_mask.cpp src/utilities/hsv_mask.cpp )
add_executable( PopColor ${SRC_LIST} )
target_link_libraries( PopColor ${OpenCV_LIBS} )