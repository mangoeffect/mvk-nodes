
project(effect_buildin_task)

include(3rdparty/VNN/VNN.cmake)

add_library(effect_buildin_task
        face_task.hpp
        face_task.cpp
        gaussian_filter_task.hpp
        gaussian_filter_task.cpp
        beauty_smooth.hpp
        beauty_smooth.cpp
        )

set_target_properties(effect_buildin_task PROPERTIES
        LINK_FLAGS "-Wl,-F${VNN_LIB_DIR}/macOS/x86_64_arm64/vnn_core_osx.framework,-F${VNN_LIB_DIR}/macOS/x86_64_arm64/vnn_face_osx.framework"
        FRAMEWORK_SEARCH_PATHS ${VNN_LIB_DIR}/macOS/x86_64_arm64
        )

target_link_libraries(effect_buildin_task
        mango_filter "-framework vnn_core_osx" "-framework vnn_face_osx"
        )