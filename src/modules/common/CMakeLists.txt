
include_directories(./include)
include_directories(./src)


set(Headers 
    ./include/common/points.h
    ./include/common/points_impl.h
    ./include/common/rectangle.h
    ./include/common/rectangle_impl.h
    ./include/common/circle.h
    ./include/common/circle_impl.h
    ./include/common/mat.h
    ./include/common/mat_impl.h
    ./include/common/rotate_rectangle.h 
    ./include/common/rotate_rectangle_impl.h
    ./include/common/line.h 
    ./include/common/line_impl.h
    ./include/common/polygon.h 
    ./include/common/polygon_impl.h
    ./include/common/algorithms.h)

set(Cpps 
    ./src/points.cpp
    ./src/points_impl.cpp
    ./src/rectangle.cpp
    ./src/rectangle_impl.cpp
    ./src/circle.cpp
    ./src/circle_impl.cpp
    ./src/mat.cpp 
    ./src/mat_impl.cpp
    ./src/rotate_rectangle.cpp 
    ./src/rotate_rectangle_impl.cpp
    ./src/line.cpp 
    ./src/line_impl.cpp
    ./src/polygon.cpp 
    ./src/polygon_impl.cpp
    ./src/algorithms/convex_hull.cpp)

if(BUILD_STATIC_LIB)
    add_definitions(-DMVK_COMMON_STATIC_DEFINE -DMVK_COMMON_STATIC_DEFINE_)
    add_library(mvk_common ${Headers} ${Cpps})
else()
    add_definitions(-DMVK_COMMON_EXPORTS -DMVK_COMMON_EXPORTS)
    add_library(mvk_common SHARED ${Headers} ${Cpps})
endif()


