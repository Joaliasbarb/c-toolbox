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
include(CTest)

function(package_add_test)
    # Input arguments parsing
    set(options "")
    set(oneValueArgs TESTNAME)
    set(multValueArgs INCLUDES SOURCES LIBS)
    cmake_parse_arguments(INPUT "${options}" "${oneValueArgs}" "${multValueArgs}" ${ARGN})

    # create an exectuable in which the tests will be stored
	message("INPUT_SOURCES: " ${INPUT_SOURCES})
	message("INPUT_INCLUDES: " ${INPUT_INCLUDES})
    add_executable(${INPUT_TESTNAME} ${INPUT_SOURCES})
	target_include_directories(${INPUT_TESTNAME} PRIVATE ${INPUT_INCLUDES})
    # link the Google test infrastructure, mocking library, and a default main function to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${INPUT_TESTNAME} PRIVATE gtest gmock gtest_main ${INPUT_LIBS})
    target_link_libraries(${INPUT_TESTNAME} PRIVATE "$<$<BOOL:${CODE_COVERAGE}>:gcov>")
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${INPUT_TESTNAME}
        # set a working directory to your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
    target_compile_options(${INPUT_TESTNAME} PRIVATE $<$<BOOL:${CODE_COVERAGE}>:-g -ftest-coverage -fprofile-arcs>)
    set_target_properties(${INPUT_TESTNAME} PROPERTIES FOLDER "test/gtest")
endfunction()

package_add_test(TESTNAME circularBufferTest SOURCES ut_circularBuffer.cpp ${PROJECT_SOURCE_DIR}/src/circularBuffer.c INCLUDES ${PROJECT_SOURCE_DIR}/include)
package_add_test(TESTNAME accurateTimerTest SOURCES ut_accurateTimer.cpp ${PROJECT_SOURCE_DIR}/src/accurateTimer.c INCLUDES ${PROJECT_SOURCE_DIR}/include)
package_add_test(TESTNAME miscUtilsTest SOURCES ut_miscUtils.cpp ${PROJECT_SOURCE_DIR}/src/miscUtils.c INCLUDES ${PROJECT_SOURCE_DIR}/include)
package_add_test(TESTNAME timerManagerTest SOURCES ut_timerManager.cpp ${PROJECT_SOURCE_DIR}/src/timerManager.c INCLUDES ${PROJECT_SOURCE_DIR}/include)