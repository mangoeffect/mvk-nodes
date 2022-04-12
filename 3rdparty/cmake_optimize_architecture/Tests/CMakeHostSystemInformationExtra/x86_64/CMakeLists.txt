cmake_minimum_required (VERSION 3.5)

if(POLICY CMP0066)
    cmake_policy(SET CMP0066 NEW)
endif()

project(CMakeHostSystemInformationExtra.X86_64 VERSION 1.0 LANGUAGES C)
include(CMakeHostSystemInformationExtra)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

  set(TEST_CPUINFO_1 "processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 78
model name	: Intel(R) Core(TM) i3-6100U CPU @ 2.30GHz
stepping	: 3
microcode	: 0xc6
cpu MHz		: 897.745
cache size	: 3072 KB
physical id	: 0
siblings	: 4
core id		: 0
cpu cores	: 2
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 22
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
bugs		: cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
bogomips	: 4608.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 39 bits physical, 48 bits virtual
power management:
")
  set(TEST_EXPECT_1 "skylake")

  foreach(testno IN ITEMS 1)
    set(_PROC_CPUINFO "/tmp/CmakeHostSystemInformationExtra__test__cpuinfo")
    file(WRITE ${_PROC_CPUINFO} "${TEST_CPUINFO_${testno}}")
    detect_x64_micro_architecture(arg1 arg2)
    if(arg2 MATCHES "${TEST_EXPECT_${testno}}")
      message(STATUS "Test ${testno} passed for ${arg2}")
    else()
      message(FATAL_ERROR "Test ${testno} got unexpected result: ${arg2}.")
    endif()
  endforeach()
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
  # TODO
endif()

# vim: ts=2 sw=2 sts=2 et
