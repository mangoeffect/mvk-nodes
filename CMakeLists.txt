cmake_minimum_required(VERSION 3.12)

project(mv-kit)

#设定安装目录
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install/")

#设定可执行二进制文件的目录
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
	
#设定存放编译出来的库文件的目录
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#并且把该目录设为连接目录
link_directories( ${PROJECT_SOURCE_DIR}/bin)

# 选择编译为动态库或静态库
option(BUILD_STATIC_LIB "Build the library as static library?" OFF)

# catch2
find_package(Catch2 REQUIRED)
include(CTest)
include(ParseAndAddCatchTests)

# data
add_definitions(-DDATA="${PROJECT_SOURCE_DIR}/data")

# 添加源代码目录
add_subdirectory(src)

