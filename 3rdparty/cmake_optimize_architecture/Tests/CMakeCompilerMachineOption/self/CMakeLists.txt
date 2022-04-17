cmake_minimum_required (VERSION 3.5)
project(CMakeCompilerMachineOption VERSION 1.0 LANGUAGES C)
include(CMakeHostSystemInformationExtra)
include(CMakeCompilerMachineOption)
cmake_host_system_information_extra(RESULT MARCH QUERY PROCESSOR_MICRO_ARCHITECTURE)
cmake_compiler_machine_option(op "${MARCH}")
add_executable(example example.c)
target_compile_options(example PRIVATE ${op})

# vim: ts=2 sw=2 sts=2 et
