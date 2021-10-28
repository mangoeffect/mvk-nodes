
include_directories(./include)
include_directories(./src)
include_directories(./3rdparty)

set(Headers 
    ./include/image/image.h
    ./include/image/image_impl.h)

set(Cpps 
    ./src/image.cpp
    ./src/image_impl.cpp)

if(BUILD_STATIC_LIB)
    add_definitions(-DMVK_IMAGE_STATIC_DEFINE -DMVK_IMAGE_STATIC_DEFINE_)
    add_library(mvk_image ${Headers} ${Cpps})
else()
    add_definitions(-DMVK_IMAGE_EXPORTS -DMVK_IMAGE_EXPORTS)
    add_library(mvk_image SHARED ${Headers} ${Cpps})
endif()


