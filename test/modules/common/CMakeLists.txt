
#包含源代码common模块include目录
include_directories(./../../../src/modules/common/include)

add_executable(test_mvk_common_mat test_mvk_common_mat.cpp)
target_link_libraries(test_mvk_common_mat mvk_common)
