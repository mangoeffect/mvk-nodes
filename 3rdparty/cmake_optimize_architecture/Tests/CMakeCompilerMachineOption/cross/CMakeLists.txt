cmake_minimum_required (VERSION 3.5)

if(POLICY CMP0066)
    cmake_policy(SET CMP0066 NEW)
endif()

project(CMakeCompilerMachineOption VERSION 1.0 LANGUAGES C)

include(CMakeCompilerMachineOption)

set(TARGET_ARCHITECTURE "knl" CACHE STRING "CPU architecture to optimize for. \
Using an incorrect setting here can result in crashes of the resulting binary because of invalid instructions used. \
Supported values: \"generic\", \"core\", \"merom\" (65nm Core2), \
\"penryn\" (45nm Core2), \"nehalem\", \"westmere\", \"sandy-bridge\", \"ivy-bridge\", \
\"haswell\", \"broadwell\", \"skylake\", \"skylake-xeon\", \"kaby-lake\", \"cannonlake\", \"silvermont\", \
\"goldmont\", \"knl\" (Knights Landing), \"atom\", \"k8\", \"k8-sse3\", \"barcelona\", \
\"istanbul\", \"magny-cours\", \"bulldozer\", \"interlagos\", \"piledriver\", \
\"amd-14h\", \"amd-16h\", \"zen\".")
cmake_compiler_machine_option(ARCHITECTURE_FLAG ${TARGET_ARCHITECTURE})
add_executable(example example.c)
target_compile_options(example PRIVATE ${ARCHITECTURE_FLAG})

# vim: ts=2 sw=2 sts=2 et
