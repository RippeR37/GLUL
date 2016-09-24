###############################################
# GLUL's basic example
###############################################

project(GLUL_EXAMPLE_BASIC CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_BASIC_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_BASIC_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_BASIC
    ${GLUL_EXAMPLE_BASIC_SOURCES}
    ${GLUL_EXAMPLE_BASIC_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_BASIC
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_BASIC PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_basic_example"
)

