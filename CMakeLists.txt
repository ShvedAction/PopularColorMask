cmake_minimum_required(VERSION 3.13)

project(PopColor VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( PopColor src/main.cpp )
target_link_libraries( PopColor ${OpenCV_LIBS} )