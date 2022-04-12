include_directories(./include)
include_directories(./src)

set(Headers 
    ./include/caliper/caliper.hpp
    ./include/caliper/caliper_impl.hpp)

set(Cpps 
    ./src/caliper.cpp
    ./src/caliper_impl.cpp)

if(BUILD_STATIC_LIB)
    add_library(mvk_caliper ${Headers} ${Cpps})
    add_definitions(-DMVK_CALIPER_EXPORT "")
else()
    add_library(mvk_caliper SHARED ${Headers} ${Cpps})
    target_include_directories(mvk_caliper PUBLIC ${PROJECT_BINARY_DIR}/exports/)
    include(GenerateExportHeader)
    generate_export_header(mvk_caliper EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/mvk_caliper_export.hpp)
endif()

target_link_libraries(mvk_caliper mvk_common mvk_image)

if(BUILD_TEST)
    add_subdirectory(test)
endif()