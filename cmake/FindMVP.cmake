cmake_minimum_required(VERSION 3.12)

if(NOT MVP_FOUND)
    set(MVP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../include")
    set(MVP_LIBRARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
    find_library(MVP_BASE_LIB NAMES base  PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    find_library(MVP_BLOBDETECT_LIB NAMES blobdetect PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    find_library(MVP_CALIPER_LIB NAMES caliper  PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    find_library(MVP_LINEFIT_LIB NAMES linefit  PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    find_library(MVP_DEBUGTOOL_LIB NAMES debugtool PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    find_library(MVP_LIBINFO_LIB NAMES libinfo PATHS ${MVP_LIBRARIES_DIR} PATH_SUFFIXES lib)
    set(MVP_LIBRARIES ${MVP_BASE_LIB} ${MVP_BLOBDETECT_LIB} ${MVP_CALIPER_LIB} ${MVP_LINEFIT_LIB} ${MVP_DEBUGTOOL_LIB} ${MVP_LIBINFO_LIB})
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(MVP DEFAULT_MSG MVP_INCLUDE_DIRS MVP_LIBRARIES_DIR MVP_LIBRARIES)
endif()