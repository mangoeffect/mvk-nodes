
project(mango_core_test)
include_directories(./)

add_executable(test_core_graph test_graph.cpp)
target_link_libraries(test_core_graph mango_core Catch2::Catch2WithMain)

add_executable(test_core_image test_image_loader_and_writer.cpp)
target_link_libraries(test_core_image mango_core Catch2::Catch2WithMain)
