###############################################
# CMake options
###############################################

cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")


###############################################
# Build options
###############################################

option(GLUL_BUILD_STATIC   "Build static library." OFF)
option(GLUL_BUILD_SHARED   "Build shared library." ON)
option(GLUL_BUILD_TESTS    "Build all tests."      ON)
option(GLUL_BUILD_EXAMPLES "Build all examples."   ON)


###############################################
# Compiler flags
###############################################

enable_language(CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(WARNINGS    "-Wall -Wextra -Werror")
    if(GLUL_BUILD_TESTS)
        set(COVERAGE_FLAGS "-g -fprofile-arcs -ftest-coverage")
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNINGS "/W4 /WX /EHsc")
endif()

if(NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS} ${COVERAGE_FLAGS}"
    CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


###############################################
# GLUL library
###############################################

add_subdirectory(project)


###############################################
# GLUL examples
###############################################

if(GLUL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


###############################################
# GLUL tests
###############################################

if(GLUL_BUILD_TESTS)
    add_subdirectory(tests)
endif()

