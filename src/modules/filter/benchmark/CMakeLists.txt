project(benchmark_filter)

add_executable(${PROJECT_NAME}_median_filter median_filter_benchmark.cpp)
target_link_libraries(${PROJECT_NAME}_median_filter mvk_filter)

add_executable(${PROJECT_NAME}_threshold threshold_benchmark.cpp)
target_link_libraries(${PROJECT_NAME}_threshold mvk_filter)

add_executable(${PROJECT_NAME}_sobel_benchmark sobel_benchmark.cpp)
target_link_libraries(${PROJECT_NAME}_sobel_benchmark mvk_filter)