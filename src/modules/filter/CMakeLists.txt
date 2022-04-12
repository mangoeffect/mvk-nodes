include_directories(./include)

set(Headers 
    ./include/filter/filter.hpp
    ./include/filter/box_filter.hpp
    ./include/filter/integral_image.hpp
    ./include/filter/gaussian_filter.hpp
    ./include/filter/median_filter.hpp)

set(Cpps 
    ./src/box_filter.cpp
    ./src/integral_image.cpp
    ./src/gaussian_filter.cpp
    ./src/median_filter.cpp)

if(BUILD_STATIC_LIB)
    add_library(mvk_filter ${Headers} ${Cpps})
    add_definitions(-DMVK_FILTER_EXPORT "")
else()
    add_library(mvk_filter SHARED ${Headers} ${Cpps})
    target_include_directories(mvk_filter PUBLIC ${PROJECT_BINARY_DIR}/exports/)
    include(GenerateExportHeader)
    generate_export_header(mvk_filter EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/mvk_filter_export.hpp)
endif()

find_package(OpenMP REQUIRED)

target_compile_options(mvk_filter PRIVATE ${ARCHITECTURE_FLAG})
target_link_libraries(mvk_filter mvk_common mvk_image xsimd OpenMP::OpenMP_CXX)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

add_subdirectory(benchmark)

