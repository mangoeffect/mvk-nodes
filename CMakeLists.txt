cmake_minimum_required(VERSION 3.12)

project(machine_vision_algorithms_library)

#Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${OpenCV_INCLUDE_DIRS})


#选择编译为动态库或静态库
option(BUILD_DYNAMIC_LIB "Build the library as dynamic library?" OFF)
if(BUILD_DYNAMIC_LIB)
    if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        add_definitions(-D BUILD_DYNAMIC_LIBRAY_ON_WINDOWS)
    endif()
endif()


add_subdirectory(src)
option(BUILD_TEST "Build the test cases" ON)
if(BUILD_TEST)
    add_subdirectory(test)
endif()

# 安装Find...cmake文件
install(DIRECTORY ./cmake DESTINATION ./
        FILES_MATCHING PATTERN "*.cmake")