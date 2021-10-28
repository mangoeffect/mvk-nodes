
include_directories(./include)
include_directories(./src)


set(Headers 


set(Cpps 

if(BUILD_STATIC_LIB)
    add_definitions(-DMVK_CALIPERS_STATIC_DEFINE -DMVK_CALIPERS_STATIC_DEFINE_)
    add_library(mvk_calipers ${Headers} ${Cpps})
else()
    add_definitions(-DMVK_CALIPERS_EXPORTS -DMVK_CALIPERS_EXPORTS)
    add_library(mvk_calipers SHARED ${Headers} ${Cpps})
endif()


