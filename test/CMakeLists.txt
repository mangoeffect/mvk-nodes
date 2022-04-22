add_executable(test_simd test_simd.cpp)
target_compile_options(test_simd PRIVATE ${ARCHITECTURE_FLAG})

add_executable(print_openmp_versioin openmp_version.cpp)
target_link_libraries(print_openmp_versioin OpenMP::OpenMP_CXX)

