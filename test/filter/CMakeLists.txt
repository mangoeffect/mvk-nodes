project(test_mango_filter)

include_directories(./)

add_executable(${PROJECT_NAME}_integral_image test_integral_image.cpp)
target_link_libraries(${PROJECT_NAME}_integral_image mango_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_box_filter test_box_filter.cpp)
target_link_libraries(${PROJECT_NAME}_box_filter mango_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_gaussian_filter test_gaussian_filter.cpp)
target_link_libraries(${PROJECT_NAME}_gaussian_filter mango_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_median_filter test_median_filter.cpp)
target_link_libraries(${PROJECT_NAME}_median_filter mango_filter Catch2::Catch2WithMain)


add_executable(${PROJECT_NAME}_threshold test_threshold.cpp)
target_link_libraries(${PROJECT_NAME}_threshold mango_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_sobel test_sobel.cpp)
target_link_libraries(${PROJECT_NAME}_sobel mango_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_blend test_blend.cpp)
target_link_libraries(${PROJECT_NAME}_blend mango_filter mango_core Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_skin_detect test_skin_detect.cpp)
target_link_libraries(${PROJECT_NAME}_skin_detect mango_filter mango_core Catch2::Catch2WithMain)