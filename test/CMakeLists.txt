cmake_minimum_required(VERSION 3.2)
project(divider_tests)

add_subdirectory(lib/googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp)

add_executable(libinfo_tests ${SOURCE_FILES})
target_link_libraries(libinfo_tests libinfo gtest)
install(TARGETS libinfo_tests DESTINATION bin)

