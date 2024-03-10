include_directories(./)

file(GLOB SOURCE "./*.cpp")

add_library(mango_core ${SOURCE})
target_compile_options(mango_core PRIVATE ${ARCHITECTURE_FLAG})
target_link_libraries(mango_core mvk_common mvk_image OpenMP::OpenMP_CXX)
