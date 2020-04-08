cmake_minimum_required(VERSION 3.2)

project(machine-vision-library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OpenCV_DIR "D:\\opencv_mingw_build_with_qt")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISIBLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(DIVISIBLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)


include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


