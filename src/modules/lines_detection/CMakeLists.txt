include_directories(./include)
include_directories(./src)

set(Headers 
./include/lines_detection/lines_detection.h 
./include/lines_detection/lines_detection_impl.h 
)

set(Cpps
./src/lines_detection.cpp 
./src/lines_detection_impl.cpp 
)

if(BUILD_STATIC_LIB)
    add_definitions(-DMVK_LINES_STATIC_DEFINE -DMVK_LINES_STATIC_DEFINE_)
    add_library(mvk_lines_detection ${Headers} ${Cpps})
else()
    add_definitions(-DMVK_LINES_EXPORTS -DMVK_LINES_EXPORTS)
    add_library(mvk_lines_detection SHARED ${Headers} ${Cpps})
endif()

target_link_libraries(mvk_lines_detection mvk_common mvk_common)