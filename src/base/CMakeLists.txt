cmake_minimum_required(VERSION 3.2)
project(base C CXX)

set(SOURCE_FILES base.h base.cpp base_test.cpp)

link_libraries(${OpenCV_LIBS})

add_library(base SHARED STATIC ${SOURCE_FILES})

add_executable(basetest base_test.cpp)
target_link_libraries(basetest base)

install(TARGETS linefit DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES linefit.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})


