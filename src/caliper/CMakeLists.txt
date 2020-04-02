cmake_minimum_required(VERSION 3.2)

project(caliper C CXX)

set(SOURCE_FILES caliper.h caliper.cpp samples.cpp)

link_libraries(${OpenCV_LIBS})

add_library(caliper SHARED STATIC ${SOURCE_FILES})

add_executable(calipersample samples.cpp)
target_link_libraries(calipersample caliper plot)

install(TARGETS caliper DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES caliper.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
