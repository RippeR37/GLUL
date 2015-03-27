cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

###############################################
# Utility Library (shared library) project
###############################################

project (Utility_Library_SHARED CXX)

# Compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(WARNINGS "-Wall -Wextra -Werror")
	set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(WARNINGS "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


# Include directoriesp paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#find_package(GLFW3)
#find_package(GLEW)
#find_packaged(GLM)

# Library sources
set(Utility_Library_SRCS
	"src/Utils/Exceptions/FatalError.cpp"
	
	"src/Utils/Frameworks/Application.cpp"
	
	"src/Utils/GL+/Models/Material.cpp"
	"src/Utils/GL+/Models/Mesh.cpp"
	"src/Utils/GL+/Models/OBJ.cpp"
	
	"src/Utils/GL+/Buffer.cpp"
	"src/Utils/GL+/Context.cpp"
	"src/Utils/GL+/Framebuffer.cpp"
	"src/Utils/GL+/MatrixStack.cpp"
	"src/Utils/GL+/Pipeline.cpp"
	"src/Utils/GL+/PixelBuffer.cpp"
	"src/Utils/GL+/Program.cpp"
	"src/Utils/GL+/Shader.cpp"
	"src/Utils/GL+/Texture.cpp"
	"src/Utils/GL+/Uniform.cpp"
	"src/Utils/GL+/VertexArray.cpp"
	"src/Utils/GL+/VertexAttrib.cpp"
	"src/Utils/GL+/VertexBuffer.cpp"
	
	"src/Utils/Interfaces/Camera.cpp"
	"src/Utils/Interfaces/Model.cpp"
	"src/Utils/Interfaces/State.cpp"
	
	"src/Utils/AABB.cpp"
	"src/Utils/Clock.cpp"
	"src/Utils/Exception.cpp"
	"src/Utils/File.cpp"
	"src/Utils/Image.cpp"
	"src/Utils/Line.cpp"
	"src/Utils/Logger.cpp"
	"src/Utils/Point.cpp"
	"src/Utils/Rectangle.cpp"
	"src/Utils/String.cpp"
	"src/Utils/TimeEvent.cpp"
	"src/Utils/TimeLoop.cpp"
	"src/Utils/Timer.cpp"
	"src/Utils/Window.cpp"
)

# Library headers
set(Utility_Library_H
	"include/Utils/Exceptions/FatalError.h"
	
	"include/Utils/Frameworks/Application.h"
	
	"include/Utils/GL+/Models/Material.h"
	"include/Utils/GL+/Models/Mesh.h"
	"include/Utils/GL+/Models/OBJ.h"
	
	"include/Utils/GL+/Buffer.h"
	"include/Utils/GL+/Buffer.hpp"
	"include/Utils/GL+/Context.h"
	"include/Utils/GL+/Framebuffer.h"
	"include/Utils/GL+/MatrixStack.h"
	"include/Utils/GL+/Pipeline.h"
	"include/Utils/GL+/PixelBuffer.h"
	"include/Utils/GL+/Program.h"
	"include/Utils/GL+/Shader.h"
	"include/Utils/GL+/Texture.h"
	"include/Utils/GL+/Uniform.h"
	"include/Utils/GL+/VertexArray.h"
	"include/Utils/GL+/VertexAttrib.h"
	"include/Utils/GL+/VertexBuffer.h"
	
	"include/Utils/Interfaces/MVC/View.h"
	"include/Utils/Interfaces/MVC/ExtendedView.h"
	
	"include/Utils/Interfaces/Camera.h"
	"include/Utils/Interfaces/Model.h"
	"include/Utils/Interfaces/State.h"
	
	"include/Utils/AABB.h"
	"include/Utils/Clock.h"
	"include/Utils/Exception.h"
	"include/Utils/File.h"
	"include/Utils/Image.h"
	"include/Utils/Line.h"
	"include/Utils/Logger.h"
	"include/Utils/Point.h"
	"include/Utils/Rectangle.h"
	"include/Utils/String.h"
	"include/Utils/TimeEvent.h"
	"include/Utils/TimeLoop.h"
	"include/Utils/Timer.h"
	"include/Utils/Window.h"
)

add_library(Utility_Library_SHARED SHARED 
	${Utility_Library_SRCS} 
	${Utility_Library_H}
)

target_link_libraries(Utility_Library_SHARED
	glfw3
	GLEW
	GL
)


###############################################
# Basic example project
###############################################

project (Utility_Library_Example_Basic CXX)

# Compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(WARNINGS "-Wall -Wextra -Werror")
	set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(WARNINGS "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


# Include directoriesp paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_Basic_SRCS
	"examples/basic/src/main.cpp"
)

set(Utility_Library_Example_Basic_H
	
)

add_executable(Utility_Library_Example_Basic 
	${Utility_Library_Example_Basic_SRCS}
	${Utility_Library_Example_Basic_H}
)

target_link_libraries(Utility_Library_Example_Basic
	Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Basic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/basic/bin/"
)

###############################################
# Framework example project
###############################################

project (Utility_Library_Example_Framework CXX)

# Compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(WARNINGS "-Wall -Wextra -Werror")
	set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(WARNINGS "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


# Include directoriesp paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_Framework_SRCS
	"examples/framework/src/main.cpp"
	"examples/framework/src/ExampleState.cpp"
)

set(Utility_Library_Example_Framework_H
	"examples/framework/src/ExampleState.h"
)

add_executable(Utility_Library_Example_Framework 
	${Utility_Library_Example_Framework_SRCS}
	${Utility_Library_Example_Framework_H}
)

target_link_libraries(Utility_Library_Example_Framework
	Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Framework PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/framework/bin/"
)

###############################################
# Models example project
###############################################

project (Utility_Library_Example_Models CXX)

# Compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(WARNINGS "-Wall -Wextra -Werror")
	set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(WARNINGS "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS}"
	CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


# Include directoriesp paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_Models_SRCS
	"examples/models/src/main.cpp"
	"examples/models/src/InitializationState.cpp"
	"examples/models/src/WorkState.cpp"
)

set(Utility_Library_Example_Models_H
	"examples/models/src/InitializationState.h"
	"examples/models/src/WorkState.h"
)

add_executable(Utility_Library_Example_Models 
	${Utility_Library_Example_Models_SRCS}
	${Utility_Library_Example_Models_H}
)

target_link_libraries(Utility_Library_Example_Models
	Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Models PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/models/bin/"
)


