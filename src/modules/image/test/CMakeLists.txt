project(test_image)


add_executable(${PROJECT_NAME} test_image.cpp)
target_link_libraries(${PROJECT_NAME} mvk_image Catch2::Catch2)
ParseAndAddCatchTests(test_image)

