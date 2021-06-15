#########################################
#            VERSION MANAGEMENT         #
#########################################
set (c-toolbox_VERSION_NAME "Alpha01")
set (c-toolbox_VERSION_MAJOR 0)
set (c-toolbox_VERSION_MINOR 1)
set (c-toolbox_VERSION_FIX 0)

# the commit's SHA1, and whether the building workspace was dirty or not
execute_process(COMMAND
    "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_SHA1
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the date of the commit
execute_process(COMMAND
    "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_DATE
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the subject of the commit
execute_process(COMMAND
    "${GIT_EXECUTABLE}" log -1 --format=%s
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)


# # configure a header file to pass some of the CMake settings
# # to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/src/utils/cToolboxVersion.h.in"
    "${PROJECT_BINARY_DIR}/src/cToolboxVersion.h")
