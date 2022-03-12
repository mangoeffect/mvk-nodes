project(test_filter)

add_executable(${PROJECT_NAME}_integral_image test_integral_image.cpp)
target_link_libraries(${PROJECT_NAME}_integral_image mvk_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_box_filter test_box_filter.cpp)
target_link_libraries(${PROJECT_NAME}_box_filter mvk_filter Catch2::Catch2WithMain)

add_executable(${PROJECT_NAME}_gaussian_filter test_gaussian_filter.cpp)
target_link_libraries(${PROJECT_NAME}_gaussian_filter mvk_filter Catch2::Catch2WithMain)


