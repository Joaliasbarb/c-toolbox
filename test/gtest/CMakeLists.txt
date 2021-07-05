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
    # link the Google test infrastructure, mocking library, and a default main function to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${INPUT_TESTNAME} PRIVATE gtest gmock gtest_main ${INPUT_LIBS})
    target_link_libraries(${INPUT_TESTNAME} PRIVATE "$<$<BOOL:${CODE_COVERAGE}>:gcov>")
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${INPUT_TESTNAME}
        # set a working directory to your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    target_compile_options(${INPUT_TESTNAME} PRIVATE $<$<BOOL:${CODE_COVERAGE}>:-g -ftest-coverage -fprofile-arcs>)
    set_target_properties(${INPUT_TESTNAME} PROPERTIES FOLDER "test/gtest")
endfunction()

package_add_test(TESTNAME circularBufferTest FILES ut_circularBuffer.cpp LIBS cToolbox)
package_add_test(TESTNAME accurateTimerTest FILES ut_accurateTimer.cpp LIBS cToolbox)
package_add_test(TESTNAME miscUtilsTest FILES ut_miscUtils.cpp LIBS cToolbox)
package_add_test(TESTNAME timerManagerTest FILES ut_timerManager.cpp LIBS cToolbox)