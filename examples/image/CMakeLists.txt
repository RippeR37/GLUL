###############################################
# GLUL's image example
###############################################

project(GLUL_EXAMPLE_IMAGE CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE GLUL_EXAMPLE_IMAGE_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLUL_EXAMPLE_IMAGE_HEADERS "src/*.h" "src/*.hpp")

add_executable(GLUL_EXAMPLE_IMAGE
    ${GLUL_EXAMPLE_IMAGE_SOURCES}
    ${GLUL_EXAMPLE_IMAGE_HEADERS}
)

target_link_libraries(GLUL_EXAMPLE_IMAGE
    GLUL_SHARED
)

set_target_properties(GLUL_EXAMPLE_IMAGE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_NAME "glul_image_example"
)

