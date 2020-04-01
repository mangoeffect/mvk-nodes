cmake_minimum_required(VERSION 3.2)

project(debugtool C CXX)

set(SOURCE_FILES plot.h plot.cpp samples.cpp)

link_libraries(${OpenCV_LIBS})

add_library(debugtool SHARED STATIC ${SOURCE_FILES})

add_executable(debugtoolsample samples.cpp)
target_link_libraries(debugtoolsample debugtool)

install(TARGETS debugtool DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES plot.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
