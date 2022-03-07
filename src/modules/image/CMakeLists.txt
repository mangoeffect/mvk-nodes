
include_directories(./include)
include_directories(./src)
include_directories(./3rdparty)

set(Headers 
    ./include/image/image_defines.hpp
    ./include/image/image.hpp
    ./include/image/image_impl.hpp)

set(Cpps 
    ./src/image.cpp
    ./src/image_impl.cpp)

if(BUILD_STATIC_LIB)
    add_library(mvk_image ${Headers} ${Cpps})
    add_definitions(-DMVK_IMAGE_EXPORT "")
else()
    add_library(mvk_image SHARED ${Headers} ${Cpps})
    target_include_directories(mvk_image PUBLIC ${PROJECT_BINARY_DIR}/exports/)
    include(GenerateExportHeader)
    generate_export_header(mvk_image EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/mvk_image_export.hpp)
endif()

target_link_libraries(mvk_image mvk_common)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

