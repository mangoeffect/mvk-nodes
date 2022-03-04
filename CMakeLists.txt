cmake_minimum_required(VERSION 3.12)

project(mv-kit)

set (CMAKE_CXX_STANDARD 20)


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

# 是否编译测试
option(BUILD_TEST "Build the test cases?" ON)
if(BUILD_TEST)
    # catch2
    Include(FetchContent)
    FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview3
    )
    FetchContent_MakeAvailable(Catch2)
    include(CTest)
endif()

# data
add_definitions(-DDATA="${PROJECT_SOURCE_DIR}/data")

# 添加源代码目录
add_subdirectory(src)

# 添加测试目录
add_subdirectory(test)

