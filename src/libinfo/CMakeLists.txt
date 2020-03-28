cmake_minimum_required(VERSION 3.2)
project(libinfo C CXX)

set(SOURCE_FILES opencvinfo.h opencvinfo.cpp samples.cpp)

link_libraries(${OpenCV_LIBS})

add_library(libinfo SHARED STATIC ${SOURCE_FILES})

add_executable(libinfosample samples.cpp)
target_link_libraries(libinfosample libinfo)

install(TARGETS libinfo DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES opencvinfo.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})


