###############################################
# GLUL's 2D example
###############################################

project(GLUL_EXAMPLE_2D CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_2D_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_2D_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_2D
    ${GLUL_EXAMPLE_2D_SOURCES}
    ${GLUL_EXAMPLE_2D_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_2D
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_2D PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_2d_example"
)

