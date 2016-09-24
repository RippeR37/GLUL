###############################################
# CMake options
###############################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")


###############################################
# GLUL dependencies
###############################################

find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

set(GLUL_LINK_LIBRARIES
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

set(GLUL_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${JPEG_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
)


###############################################
# GLUL headers & sources
###############################################

file(GLOB_RECURSE GLUL_HEADERS 
    "${CMAKE_SOURCE_DIR}/include/*.h" 
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

file(GLOB_RECURSE GLUL_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)


###############################################
# GLUL (static library) project
###############################################

if(GLUL_BUILD_STATIC)
    project(GLUL_STATIC CXX)

    include_directories(${GLUL_INCLUDE_DIRS})
    add_library(GLUL_STATIC STATIC ${GLUL_SOURCES} ${GLUL_HEADERS})
    set_target_properties(GLUL_STATIC PROPERTIES OUTPUT_NAME GLUL)
endif()


###############################################
# GLUL (shared library) project
###############################################

if(GLUL_BUILD_SHARED)
    project(GLUL_SHARED CXX)

    include_directories(${GLUL_INCLUDE_DIRS})
    add_library(GLUL_SHARED SHARED ${GLUL_SOURCES} ${GLUL_HEADERS})
    target_link_libraries(GLUL_SHARED ${GLUL_LINK_LIBRARIES})
    set_target_properties(GLUL_SHARED PROPERTIES OUTPUT_NAME GLUL)
endif()

