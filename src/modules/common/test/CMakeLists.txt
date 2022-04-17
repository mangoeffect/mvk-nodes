project(test_common)


add_executable(${PROJECT_NAME}_mat test_mat.cpp)
target_link_libraries(${PROJECT_NAME}_mat mvk_common Catch2::Catch2WithMain)


add_executable(${PROJECT_NAME}_point test_point.cpp)
target_link_libraries(${PROJECT_NAME}_point mvk_common Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_algorithms_gemm1 test_algorithms_gemm1.cpp)
target_link_libraries(${PROJECT_NAME}_algorithms_gemm1 mvk_common Catch2::Catch2WithMain)

