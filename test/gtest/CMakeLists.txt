cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

function(package_add_test)
    # Input arguments parsing
    set(options "")
    set(oneValueArgs TESTNAME)
    set(multValueArgs FILES LIBS)
    cmake_parse_arguments(INPUT "${options}" "${oneValueArgs}" "${multValueArgs}" ${ARGN})

    # create an exectuable in which the tests will be stored
    add_executable(${INPUT_TESTNAME} ${INPUT_FILES})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${INPUT_TESTNAME} gtest gmock gtest_main ${INPUT_LIBS})
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${INPUT_TESTNAME}
        # set a working directory to your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${INPUT_TESTNAME} PROPERTIES FOLDER test/gtest)
endfunction()

package_add_test(TESTNAME circularBufferTest FILES gtest_circularBuffer.cpp LIBS cToolbox)