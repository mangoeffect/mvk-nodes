
include_directories(./include)
include_directories(./src)


set(Headers 
    ./include/common/point.hpp
    ./include/common/rectangle.hpp
    ./include/common/circle.hpp
    ./include/common/mat.hpp
    ./include/common/rotate_rectangle.hpp 
    ./include/common/line.hpp 
    ./include/common/polygon.hpp 
    ./include/common/algorithms.hpp
    ./include/common/common_defines.hpp)

set(Cpps 
    ./src/point.cpp
    ./src/rectangle.cpp
    ./src/circle.cpp
    ./src/mat.cpp 
    ./src/rotate_rectangle.cpp 
    ./src/line.cpp 
    ./src/polygon.cpp 
    ./src/algorithms/convex_hull.cpp)

if(BUILD_STATIC_LIB)
    add_definitions(-DMVK_COMMON_STATIC_DEFINE -DMVK_COMMON_STATIC_DEFINE_)
    add_library(mvk_common ${Headers} ${Cpps})
else()
    add_definitions(-DMVK_COMMON_EXPORTS -DMVK_COMMON_EXPORTS)
    add_library(mvk_common SHARED ${Headers} ${Cpps})
endif()

if(BUILD_TEST)
    add_subdirectory(test)
endif()
