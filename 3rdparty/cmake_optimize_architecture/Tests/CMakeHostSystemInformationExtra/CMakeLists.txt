add_test(NAME "CMakeHostSystemInformationExtra.arm"
         COMMAND "${CMAKE_CTEST_COMMAND}"
         --build-and-test
         "${CMAKE_SOURCE_DIR}/Tests/CMakeHostSystemInformationExtra/arm"
         "${CMAKE_BINARY_DIR}/Tests/CMakeHostSystemInformationExtra/arm"
         --build-generator ${CMAKE_GENERATOR}
         --build-project CMakeHostSystemInformationExtra
         --build-options -DCMAKE_MODULE_PATH=${CMAKE_SOURCE_DIR}/Modules
         --test-command ${CMAKE_CTEST_COMMAND} -C ${CTestTest_CONFIG}
         )
add_test(NAME "CMakeHostSystemInformationExtra.x64"
         COMMAND "${CMAKE_CTEST_COMMAND}"
         --build-and-test
         "${CMAKE_SOURCE_DIR}/Tests/CMakeHostSystemInformationExtra/x86_64"
         "${CMAKE_BINARY_DIR}/Tests/CMakeHostSystemInformationExtra/x86_64"
         --build-generator ${CMAKE_GENERATOR}
         --build-project CMakeHostSystemInformationExtra
         --build-options -DCMAKE_MODULE_PATH=${CMAKE_SOURCE_DIR}/Modules
         --test-command ${CMAKE_CTEST_COMMAND} -C ${CTestTest_CONFIG}
         )
