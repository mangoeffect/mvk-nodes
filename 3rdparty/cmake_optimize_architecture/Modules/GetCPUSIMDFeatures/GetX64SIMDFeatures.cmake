# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
GetX64SIMDFeatures
------------------

  Get feature list for target Intel micro architecture

.. command:: get_x64_simd_features

   get_x64_simd_features(<output variable> <target architecture>)

 supported targets are: "none", "generic", "core", "merom" (65nm Core2),
    "penryn" (45nm Core2), "nehalem", "westmere", "sandy-bridge", "ivy-bridge",
    "haswell", "broadwell", "skylake", "skylake-xeon", "kabylake", "coffelake",
    "cannonlake", "silvermont",
    "goldmont", "knl" (Knights Landing), "atom", "k8", "k8-sse3", "barcelona",
    "istanbul", "magny-cours", "bulldozer", "interlagos", "piledriver",
    "AMD-14h", "AMD-16h", "zen".
#]=======================================================================]

function(GET_X64_SIMD_FEATURES outvar tarch)
    if(tarch STREQUAL "penryn")
        set(_available_vector_units_list "sse" "sse2" "sse3" "ssse3")
        message(STATUS "Sadly the Penryn architecture exists in variants with SSE4.1 and without SSE4.1.")
        if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            file(READ "/proc/cpuinfo" _cpuinfo)
            string(REGEX REPLACE ".*flags[ \t]*:[ \t]+([^\n]+).*" "\\1" _cpu_flags "${_cpuinfo}")
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
            exec_program("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE _sysctl_output_string)
            string(TOLOWER "${_sysctl_output_string}" _cpu_flags)
            string(REPLACE "." "_" _cpu_flags "${_cpu_flags}")
        else()
            set(_cpu_flags)
        endif()
        if(_cpu_flags MATCHES "sse4_1")
            list(APPEND _available_vector_units_list "sse4.1")
        else()
            message(STATUS "SSE4.1: disabled (auto-detected from this computer's CPU flags)")
        endif()
        set(${outvar} ${_available_vector_units_list} PARENT_SCOPE)
    else()
        set(_arch_core      "sse" "sse2" "sse3")
        set(_arch_merom     "sse" "sse2" "sse3" "ssse3")
        set(_arch_penryn    "sse" "sse2" "sse3" "ssse3")
        set(_arch_knl       "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "avx512f" "avx512pf" "avx512er" "avx512cd")
        set(_arch_knm       "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "avx512f" "avx512cd" "avx512dq" "avx512bw" "avx512vl" "avx512ifma" "avx512vbmi" "avx512_4fmaps")
        set(_arch_cannonlake "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "avx512f" "avx512cd" "avx512dq" "avx512bw" "avx512vl" "avx512ifma" "avx512vbmi")
        set(_arch_coffelake "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2")
        set(_arch_kabylake   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2")
        set(_arch_skylake-xeon   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "avx512f" "avx512cd" "avx512dq" "avx512bw" "avx512vl")
        set(_arch_skylake-avx512 "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "avx512f" "avx512cd" "avx512dq" "avx512bw" "avx512vl")
        set(_arch_skylake   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2")
        set(_arch_broadwell "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2")
        set(_arch_haswell   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2")
        set(_arch_ivy-bridge "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "avxi" "rdrnd" "f16c")
        set(_arch_sandy-bridge "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx")
        set(_arch_westmere   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2")
        set(_arch_nehalem    "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2")
        set(_arch_goldmont   "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "rdrnd")
        set(_arch_silvermont "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "rdrnd")
        set(_arch_atom       "sse" "sse2" "sse3" "ssse3")
        set(_arch_k8         "sse" "sse2")
        set(_arch_k8-sse3    "sse" "sse2" "sse3")
        set(_arch_AMD-16h    "sse" "sse2" "sse3" "ssse3" "sse4a" "sse4.1" "sse4.2" "avx" "f16c")
        set(_arch_AMD-14h    "sse" "sse2" "sse3" "ssse3" "sse4a")
        set(_arch_zen        "sse" "sse2" "sse3" "ssse3" "sse4.1" "sse4.2" "avx" "rdrnd" "f16c" "avx2" "fma" "bmi" "bmi2" "sse4a")
        set(_arch_piledriver "sse" "sse2" "sse3" "ssse3" "sse4a" "sse4.1" "sse4.2" "avx" "xop" "fma4" "fma" "f16c")
        set(_arch_interlagos "sse" "sse2" "sse3" "ssse3" "sse4a" "sse4.1" "sse4.2" "avx" "xop" "fma4")
        set(_arch_bulldozer  "sse" "sse2" "sse3" "ssse3" "sse4a" "sse4.1" "sse4.2" "avx" "xop" "fma4")
        set(_arch_barcelona  "sse" "sse2" "sse3" "sse4a")
        set(_arch_istanbul   "sse" "sse2" "sse3" "sse4a")
        set(_arch_magny-cours "sse" "sse2" "sse3" "sse4a")

        if(DEFINED _arch_${tarch})
            set(${outvar} ${_arch_${tarch}} PARENT_SCOPE)
        elseif(tarch STREQUAL "generic" OR
               tarch STREQUAL "none")
            set(${outvar} "" PARENT_SCOPE)
        else()
            message(WARNING "Unknown target architecture: \"${tarch}\".")
            set(${outvar} "-NOT-FOUND" PARENT_SCOPE)
        endif()
    endif()
endfunction()
