cmake_minimum_required(VERSION 3.2)
project(blobdetect C CXX)

set(SOURCE_FILES blobdetect.h blobdetect.cpp samples.cpp)

link_libraries(${OpenCV_LIBS})

add_library(blobdetect SHARED STATIC ${SOURCE_FILES})

add_executable(blobdetectsample samples.cpp)
target_link_libraries(blobdetectsample blobdetect)

install(TARGETS blobdetect DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES blobdetect.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
