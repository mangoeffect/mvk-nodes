cmake_minimum_required(VERSION 3.12)

project(mv-kit)

# 选择编译为动态库或静态库
option(BUILD_STATIC_LIB "Build the library as static library?" OFF)

# 添加源代码目录
add_subdirectory(src)

