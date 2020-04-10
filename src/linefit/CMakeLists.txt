cmake_minimum_required(VERSION 3.2)
project(linefit C CXX)

set(SOURCE_FILES linefit.h linefit.cpp samples.cpp)

link_libraries(${OpenCV_LIBS})

add_library(linefit SHARED STATIC ${SOURCE_FILES})

add_executable(linefitsample samples.cpp)
target_link_libraries(linefitsample linefit)

install(TARGETS linefit DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES linefit.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})


