###############################################
# GLUL's input example
###############################################

project(GLUL_EXAMPLE_INPUT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_INPUT_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_INPUT_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_INPUT
    ${GLUL_EXAMPLE_INPUT_SOURCES}
    ${GLUL_EXAMPLE_INPUT_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_INPUT
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_INPUT PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_input_example"
)

