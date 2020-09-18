cmake_minimum_required(VERSION 3.12)

project(blobdetect)

aux_source_directory(. CURRENT_DIR_SRCS)

if(BUILD_DYNAMIC_LIB)
  add_library(${PROJECT_NAME} SHARED  ${CURRENT_DIR_SRCS})
else()
  add_library(${PROJECT_NAME} STATIC  ${CURRENT_DIR_SRCS})
endif()


target_link_libraries(${PROJECT_NAME}
${OpenCV_LIBS}
${PCL_LIBRARIES}
${OPENMESH_LIBRARIES})


# 安装 include 文件
install(DIRECTORY ./ DESTINATION include/mvp/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h")


# 将库文件，可执行文件，头文件安装到指定目录
install(TARGETS ${PROJECT_NAME}
        EXPORT GoodScan3D
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
