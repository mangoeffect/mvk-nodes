project(test_caliper)

add_executable(test_caliper test_caliper.cpp)
target_link_libraries(test_caliper mvk_caliper mvk_filter Python3::Python  Python3::NumPy)
