add_executable(test_xsimd test_xsimd.cpp)
target_link_libraries(test_xsimd xsimd)
target_compile_options(test_xsimd PRIVATE ${ARCHITECTURE_FLAG})





