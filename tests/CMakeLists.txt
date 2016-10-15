###############################################
# Unit tests
###############################################

enable_testing()

find_package (Threads)
find_package (GTest REQUIRED)

file(GLOB_RECURSE GLUL_UNIT_TEST_HEADERS "src/*.h" "src/*.hpp")
file(GLOB_RECURSE GLUL_UNIT_TEST_SOURCES "src/*.cpp")

add_executable(GLUL_UNIT_TESTS
    ${GLUL_UNIT_TEST_SOURCES}
    ${GLUL_UNIT_TEST_HEADERS}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

target_link_libraries(GLUL_UNIT_TESTS
    GLUL_SHARED
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(NAME GLUL_UNIT_TESTS COMMAND glul_unit_tests)

set_target_properties(GLUL_UNIT_TESTS PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_unit_tests"
)

