cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE /home/mango/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(opencv-benchmark)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(median-filter)