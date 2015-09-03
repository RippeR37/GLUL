cmake_minimum_required (VERSION 2.8 FATAL_ERROR)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


###############################################
# Build options
###############################################

option(BUILD_TESTS "Build all tests." OFF)


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


# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include directories for libraries
set(LIBRARY_INCLUDE_DIR_GLFW "/usr/local/include/GLFW")
set(LIBRARY_INCLUDE_DIR_GLEW "/usr/include/GL/")
set(LIBRARY_INCLUDE_DIR_GLM "/usr/local/include/glm/")
set(LIBRARY_INCLUDE_DIR_FREETYPE2 "/usr/include/freetype2/")
set(LIBRARY_INCLUDE_DIR_LIBJPEG "/usr/local/include/")
set(LIBRARY_INCLUDE_DIR_LIBPNG "/usr/include/libpng/")

include_directories(${LIBRARY_INCLUDE_DIR_GLFW})
include_directories(${LIBRARY_INCLUDE_DIR_GLEW})
include_directories(${LIBRARY_INCLUDE_DIR_GLM})
include_directories(${LIBRARY_INCLUDE_DIR_FREETYPE2})
include_directories(${LIBRARY_INCLUDE_DIR_LIBJPEG})
include_directories(${LIBRARY_INCLUDE_DIR_LIBPNG})

# Library sources
set(Utility_Library_SRCS
    "src/Utils/Exceptions/FatalError.cpp"
    "src/Utils/Exceptions/InitializationFailed.cpp"
    "src/Utils/Exceptions/InvalidArgument.cpp"
    
    "src/Utils/Frameworks/Application.cpp"
    
    "src/Utils/GL+/GUI/Events/KeyStroke.cpp"
    "src/Utils/GL+/GUI/Events/MouseClick.cpp"
    "src/Utils/GL+/GUI/Events/MouseEnter.cpp"
    "src/Utils/GL+/GUI/Events/MouseLeave.cpp"
    "src/Utils/GL+/GUI/Events/MouseMove.cpp"
    "src/Utils/GL+/GUI/Events/MouseRelease.cpp"
    
    "src/Utils/GL+/GUI/Styles/Border.cpp"
    
    "src/Utils/GL+/GUI/Button.cpp"
    "src/Utils/GL+/GUI/Component.cpp"
    "src/Utils/GL+/GUI/Container.cpp"
    "src/Utils/GL+/GUI/Font.cpp"
    "src/Utils/GL+/GUI/InnerText.cpp"
    "src/Utils/GL+/GUI/Text.cpp"
    "src/Utils/GL+/GUI/TextField.cpp"
    "src/Utils/GL+/GUI/Window.cpp"
    
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
    
    "src/Utils/Input/EventTypes/KeyEvent.cpp"
    "src/Utils/Input/EventTypes/MouseButtonEvent.cpp"
    "src/Utils/Input/EventTypes/MouseMovementEvent.cpp"
    "src/Utils/Input/EventTypes/MouseScrollEvent.cpp"
    
    "src/Utils/Input/Event.cpp"
    "src/Utils/Input/EventAggregator.cpp"
    "src/Utils/Input/EventHandler.cpp"
    "src/Utils/Input/EventTrigger.cpp"
	"src/Utils/Input/Keyboard.cpp"
    "src/Utils/Input/Mouse.cpp"
    
    "src/Utils/Interfaces/Implementations/ImageFileBMP.cpp"
    "src/Utils/Interfaces/Implementations/ImageFileJPG.cpp"
    "src/Utils/Interfaces/Implementations/ImageFilePNG.cpp"
    "src/Utils/Interfaces/Implementations/ImageFileTGA.cpp"
    
    "src/Utils/Interfaces/Camera.cpp"
    "src/Utils/Interfaces/ImageFile.cpp"
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
    "src/Utils/Windows.cpp"
)

# Library headers
set(Utility_Library_H
    "include/Utils/Exceptions/FatalError.h"
    "include/Utils/Exceptions/InitializationFailed.h"
    "include/Utils/Exceptions/InvalidArgument.h"
	
    "include/Utils/Frameworks/Application.h"
    
    "include/Utils/GL+/GUI/Events/EventTemplate.hpp"
    "include/Utils/GL+/GUI/Events/HandlerAggregator.hpp"
    "include/Utils/GL+/GUI/Events/KeyStroke.h"
    "include/Utils/GL+/GUI/Events/MouseClick.h"
    "include/Utils/GL+/GUI/Events/MouseEnter.h"
    "include/Utils/GL+/GUI/Events/MouseLeave.h"
    "include/Utils/GL+/GUI/Events/MouseMove.h"
    "include/Utils/GL+/GUI/Events/MouseRelease.h"
    
    "include/Utils/GL+/GUI/Styles/Border.h"
    "include/Utils/GL+/GUI/Styles/HorizontalAlignment.h"
    "include/Utils/GL+/GUI/Styles/VerticalAlignment.h"
    
    "include/Utils/GL+/GUI/Button.h"
    "include/Utils/GL+/GUI/Component.h"
    "include/Utils/GL+/GUI/Container.h"
    "include/Utils/GL+/GUI/Font.h"
    "include/Utils/GL+/GUI/InnerText.h"
    "include/Utils/GL+/GUI/Text.h"
    "include/Utils/GL+/GUI/TextField.h"
    "include/Utils/GL+/GUI/Window.h"
    
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
    
    "include/Utils/Helpers/HashEnum.h"
    
    "include/Utils/Input/EventTypes/KeyEvent.h"
    "include/Utils/Input/EventTypes/MouseButtonEvent.h"
    "include/Utils/Input/EventTypes/MouseMovementEvent.h"
    "include/Utils/Input/EventTypes/MouseScrollEvent.h"
    
    "include/Utils/Input/Event.h"
    "include/Utils/Input/EventAggregator.h"
    "include/Utils/Input/EventHandler.h"
    "include/Utils/Input/EventTrigger.h"
    "include/Utils/Input/Keyboard.h"
    "include/Utils/Input/Mouse.h"
    "include/Utils/Input/Types.h"
    
    "include/Utils/Interfaces/Implementations/ImageFileBMP.h"
    "include/Utils/Interfaces/Implementations/ImageFileJPG.h"
    "include/Utils/Interfaces/Implementations/ImageFilePNG.h"
    "include/Utils/Interfaces/Implementations/ImageFileTGA.h"
    
    "include/Utils/Interfaces/MVC/View.h"
    "include/Utils/Interfaces/MVC/ExtendedView.h"
    
    "include/Utils/Interfaces/Camera.h"
    "include/Utils/Interfaces/ImageFile.h"
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
    "include/Utils/Windows.h"
)

add_library(Utility_Library_SHARED SHARED 
    ${Utility_Library_SRCS} 
    ${Utility_Library_H}
)

target_link_libraries(Utility_Library_SHARED
    glfw            # GLFW3
    GLEW            # GLEW
    GL              # OpenGL
    freetype        # freetype2
    png             # libpng
    jpeg            # libjpeg
    z               # zlib
)


###############################################
# Unit tests
###############################################

if(BUILD_TESTS)
    enable_testing()

    set(Utility_Library_Unit_Tests_SRCS
        "tests/src/main.cpp"
        
        "tests/src/Utils/Clock.cpp"
        "tests/src/Utils/Line.cpp"
        "tests/src/Utils/Point.cpp"
        "tests/src/Utils/String.cpp"
    )

    set(Utility_Library_Unit_Tests_H
        
    )

    add_executable(Utility_Library_Unit_Tests 
        ${Utility_Library_Unit_Tests_SRCS}
        ${Utility_Library_Unit_Tests_H}
    )

    target_link_libraries(Utility_Library_Unit_Tests 
        gtest
        gtest_main
    )

    target_link_libraries(Utility_Library_Unit_Tests
        Utility_Library_SHARED
    )

    add_test(
        NAME UtilityLibraryUnitTests 
        COMMAND Utility_Library_Unit_Tests
    )

    set_target_properties(Utility_Library_Unit_Tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "tests/bin/"
    )

endif()


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


# Include directories paths
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
# Font example project
###############################################

project (Utility_Library_Example_Font CXX)

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


# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_Font_SRCS
    "examples/font/src/main.cpp"
)

set(Utility_Library_Example_Font_H
    
)

add_executable(Utility_Library_Example_Font 
    ${Utility_Library_Example_Font_SRCS}
    ${Utility_Library_Example_Font_H}
)

target_link_libraries(Utility_Library_Example_Font
    Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Font PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/font/bin/"
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


# Include directories paths
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
# Image example project
###############################################

project (Utility_Library_Example_Image CXX)

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


# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_Image_SRCS
    "examples/image/src/main.cpp"
)

set(Utility_Library_Example_Image_H
    "examples/models/src/InitializationState.h"
    "examples/models/src/WorkState.h"
)

add_executable(Utility_Library_Example_Image 
    ${Utility_Library_Example_Image_SRCS}
    ${Utility_Library_Example_Image_H}
)

target_link_libraries(Utility_Library_Example_Image
    Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Image PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/image/bin/"
)

###############################################
# Input example project
###############################################

project (Utility_Library_Example_Input CXX)

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


# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build input example
set(Utility_Library_Example_Input_SRCS
    "examples/input/src/main.cpp"
)

set(Utility_Library_Example_Input_H
    
)

add_executable(Utility_Library_Example_Input 
    ${Utility_Library_Example_Input_SRCS}
    ${Utility_Library_Example_Input_H}
)

target_link_libraries(Utility_Library_Example_Input
    Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_Input PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/input/bin/"
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


# Include directories paths
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

###############################################
# GUI example project
###############################################

project (Utility_Library_Example_GUI CXX)

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


# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(Utility_Library_Example_GUI_SRCS
    "examples/gui/src/main.cpp"
)

set(Utility_Library_Example_GUI_H
    
)

add_executable(Utility_Library_Example_GUI 
    ${Utility_Library_Example_GUI_SRCS}
    ${Utility_Library_Example_GUI_H}
)

target_link_libraries(Utility_Library_Example_GUI
    Utility_Library_SHARED
)

set_target_properties(Utility_Library_Example_GUI PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/gui/bin/"
)
