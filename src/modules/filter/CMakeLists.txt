set(Headers
        filter.hpp
        box_filter.hpp
        integral_image.hpp
        gaussian_filter.hpp
        median_filter.hpp
        threshold.hpp
        blend.hpp
        skin_detect.hpp
        sobel.hpp)

set(Cpps
        box_filter.cpp
        integral_image.cpp
        gaussian_filter.cpp
        median_filter.cpp
        threshold.cpp
        blend.cpp
        skin_detect.cpp
        sobel.cpp)

add_library(mango_filter ${Headers} ${Cpps})


target_compile_options(mango_filter PRIVATE ${ARCHITECTURE_FLAG})
target_link_libraries(mango_filter mango_core OpenMP::OpenMP_CXX)





