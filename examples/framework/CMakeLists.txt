###############################################
# GLUL's framework example
###############################################

project(GLUL_EXAMPLE_FRAMEWORK CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_FRAMEWORK_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_FRAMEWORK_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_FRAMEWORK
    ${GLUL_EXAMPLE_FRAMEWORK_SOURCES}
    ${GLUL_EXAMPLE_FRAMEWORK_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_FRAMEWORK
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_FRAMEWORK PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_framework_example"
)

