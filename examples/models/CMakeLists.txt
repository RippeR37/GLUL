###############################################
# GLUL's models example
###############################################

project(GLUL_EXAMPLE_MODELS CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_MODELS_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_MODELS_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_MODELS
    ${GLUL_EXAMPLE_MODELS_SOURCES}
    ${GLUL_EXAMPLE_MODELS_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_MODELS
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_MODELS PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_models_example"
)

