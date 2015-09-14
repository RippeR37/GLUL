cmake_minimum_required (VERSION 2.8 FATAL_ERROR)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


###############################################
# Build options
###############################################

option(BUILD_TESTS "Build all tests." OFF)


###############################################
# Compiler flags
###############################################

enable_language(CXX)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(WARNINGS "-Wall -Wextra -Werror")
    set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNINGS "/W4 /WX /EHsc")
endif()

if(BUILD_TESTS AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   set(COVERAGE_FLAGS "-g -fprofile-arcs -ftest-coverage")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS} ${COVERAGE_FLAGS}"
    CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


###############################################
# GLUL source files
###############################################

set(GLUL_SRCS
    "src/GLUL/Exceptions/FatalError.cpp"
    "src/GLUL/Exceptions/InitializationFailed.cpp"
    "src/GLUL/Exceptions/InvalidArgument.cpp"
    
    "src/GLUL/Frameworks/Application.cpp"
    
    "src/GLUL/GL++/Models/Material.cpp"
    "src/GLUL/GL++/Models/Mesh.cpp"
    "src/GLUL/GL++/Models/OBJ.cpp"
    
    "src/GLUL/GL++/Buffer.cpp"
    "src/GLUL/GL++/Context.cpp"
    "src/GLUL/GL++/Framebuffer.cpp"
    "src/GLUL/GL++/MatrixStack.cpp"
    "src/GLUL/GL++/Pipeline.cpp"
    "src/GLUL/GL++/PixelBuffer.cpp"
    "src/GLUL/GL++/Program.cpp"
    "src/GLUL/GL++/Shader.cpp"
    "src/GLUL/GL++/Texture.cpp"
    "src/GLUL/GL++/Uniform.cpp"
    "src/GLUL/GL++/VertexArray.cpp"
    "src/GLUL/GL++/VertexAttrib.cpp"
    "src/GLUL/GL++/VertexBuffer.cpp"
    
    "src/GLUL/GUI/Events/KeyStroke.cpp"
    "src/GLUL/GUI/Events/MouseClick.cpp"
    "src/GLUL/GUI/Events/MouseEnter.cpp"
    "src/GLUL/GUI/Events/MouseLeave.cpp"
    "src/GLUL/GUI/Events/MouseMove.cpp"
    "src/GLUL/GUI/Events/MouseRelease.cpp"
    "src/GLUL/GUI/Events/TextInput.cpp"
    
    "src/GLUL/GUI/Styles/Border.cpp"
    
    "src/GLUL/GUI/Button.cpp"
    "src/GLUL/GUI/Checkbox.cpp"
    "src/GLUL/GUI/Component.cpp"
    "src/GLUL/GUI/Container.cpp"
    "src/GLUL/GUI/Font.cpp"
    "src/GLUL/GUI/InnerText.cpp"
    "src/GLUL/GUI/Text.cpp"
    "src/GLUL/GUI/TextField.cpp"
    "src/GLUL/GUI/Window.cpp"
    
    "src/GLUL/Input/EventTypes/CharacterEvent.cpp"
    "src/GLUL/Input/EventTypes/KeyEvent.cpp"
    "src/GLUL/Input/EventTypes/MouseButtonEvent.cpp"
    "src/GLUL/Input/EventTypes/MouseMovementEvent.cpp"
    "src/GLUL/Input/EventTypes/MouseScrollEvent.cpp"
    
    "src/GLUL/Input/Event.cpp"
    "src/GLUL/Input/EventAggregator.cpp"
    "src/GLUL/Input/EventHandler.cpp"
    "src/GLUL/Input/EventTrigger.cpp"
    "src/GLUL/Input/Keyboard.cpp"
    "src/GLUL/Input/Mouse.cpp"
    
    "src/GLUL/Interfaces/Implementations/ImageFileBMP.cpp"
    "src/GLUL/Interfaces/Implementations/ImageFileJPG.cpp"
    "src/GLUL/Interfaces/Implementations/ImageFilePNG.cpp"
    "src/GLUL/Interfaces/Implementations/ImageFileTGA.cpp"
    
    "src/GLUL/Interfaces/Camera.cpp"
    "src/GLUL/Interfaces/ImageFile.cpp"
    "src/GLUL/Interfaces/Model.cpp"
    "src/GLUL/Interfaces/State.cpp"
    
    "src/GLUL/AABB.cpp"
    "src/GLUL/Clock.cpp"
    "src/GLUL/Exception.cpp"
    "src/GLUL/File.cpp"
    "src/GLUL/Image.cpp"
    "src/GLUL/Line.cpp"
    "src/GLUL/Logger.cpp"
    "src/GLUL/Point.cpp"
    "src/GLUL/Rectangle.cpp"
    "src/GLUL/String.cpp"
    "src/GLUL/TimeEvent.cpp"
    "src/GLUL/TimeLoop.cpp"
    "src/GLUL/Timer.cpp"
    "src/GLUL/Window.cpp"
    "src/GLUL/Windows.cpp"
)


###############################################
# GLUL header files
###############################################

set(GLUL_H
    "include/GLUL/Exceptions/FatalError.h"
    "include/GLUL/Exceptions/InitializationFailed.h"
    "include/GLUL/Exceptions/InvalidArgument.h"
    
    "include/GLUL/Frameworks/Application.h"
    
    "include/GLUL/GL++/Models/Material.h"
    "include/GLUL/GL++/Models/Mesh.h"
    "include/GLUL/GL++/Models/OBJ.h"
    
    "include/GLUL/GL++/Buffer.h"
    "include/GLUL/GL++/Buffer.hpp"
    "include/GLUL/GL++/Context.h"
    "include/GLUL/GL++/Framebuffer.h"
    "include/GLUL/GL++/MatrixStack.h"
    "include/GLUL/GL++/Pipeline.h"
    "include/GLUL/GL++/PixelBuffer.h"
    "include/GLUL/GL++/Program.h"
    "include/GLUL/GL++/Shader.h"
    "include/GLUL/GL++/Texture.h"
    "include/GLUL/GL++/Uniform.h"
    "include/GLUL/GL++/VertexArray.h"
    "include/GLUL/GL++/VertexAttrib.h"
    "include/GLUL/GL++/VertexBuffer.h"
    
    "include/GLUL/GUI/Events/EventTemplate.hpp"
    "include/GLUL/GUI/Events/HandlerAggregator.hpp"
    "include/GLUL/GUI/Events/KeyStroke.h"
    "include/GLUL/GUI/Events/MouseClick.h"
    "include/GLUL/GUI/Events/MouseEnter.h"
    "include/GLUL/GUI/Events/MouseLeave.h"
    "include/GLUL/GUI/Events/MouseMove.h"
    "include/GLUL/GUI/Events/MouseRelease.h"
    "include/GLUL/GUI/Events/TextInput.h"
    
    "include/GLUL/GUI/Styles/Border.h"
    "include/GLUL/GUI/Styles/HorizontalAlignment.h"
    "include/GLUL/GUI/Styles/VerticalAlignment.h"
    
    "include/GLUL/GUI/Button.h"
    "include/GLUL/GUI/Checkbox.h"
    "include/GLUL/GUI/Component.h"
    "include/GLUL/GUI/Container.h"
    "include/GLUL/GUI/Font.h"
    "include/GLUL/GUI/InnerText.h"
    "include/GLUL/GUI/Text.h"
    "include/GLUL/GUI/TextField.h"
    "include/GLUL/GUI/Window.h"
    
    "include/GLUL/Helpers/HashEnum.h"
    
    "include/GLUL/Input/EventTypes/CharacterEvent.h"
    "include/GLUL/Input/EventTypes/KeyEvent.h"
    "include/GLUL/Input/EventTypes/MouseButtonEvent.h"
    "include/GLUL/Input/EventTypes/MouseMovementEvent.h"
    "include/GLUL/Input/EventTypes/MouseScrollEvent.h"
    
    "include/GLUL/Input/Event.h"
    "include/GLUL/Input/EventAggregator.h"
    "include/GLUL/Input/EventHandler.h"
    "include/GLUL/Input/EventTrigger.h"
    "include/GLUL/Input/Keyboard.h"
    "include/GLUL/Input/Mouse.h"
    "include/GLUL/Input/Types.h"
    
    "include/GLUL/Interfaces/Implementations/ImageFileBMP.h"
    "include/GLUL/Interfaces/Implementations/ImageFileJPG.h"
    "include/GLUL/Interfaces/Implementations/ImageFilePNG.h"
    "include/GLUL/Interfaces/Implementations/ImageFileTGA.h"
    
    "include/GLUL/Interfaces/MVC/View.h"
    "include/GLUL/Interfaces/MVC/ExtendedView.h"
    
    "include/GLUL/Interfaces/Camera.h"
    "include/GLUL/Interfaces/ImageFile.h"
    "include/GLUL/Interfaces/Model.h"
    "include/GLUL/Interfaces/State.h"
    
    "include/GLUL/AABB.h"
    "include/GLUL/Clock.h"
    "include/GLUL/Exception.h"
    "include/GLUL/File.h"
    "include/GLUL/Image.h"
    "include/GLUL/Line.h"
    "include/GLUL/Logger.h"
    "include/GLUL/Point.h"
    "include/GLUL/Rectangle.h"
    "include/GLUL/String.h"
    "include/GLUL/TimeEvent.h"
    "include/GLUL/TimeLoop.h"
    "include/GLUL/Timer.h"
    "include/GLUL/Window.h"
    "include/GLUL/Windows.h"
)


###############################################
# GLUL dependencies setup
###############################################

# Include directories for dependencies
set(LIBRARY_INCLUDE_DIR_GLFW "/usr/local/include/GLFW")
set(LIBRARY_INCLUDE_DIR_GLEW "/usr/include/GL/")
set(LIBRARY_INCLUDE_DIR_GLM "/usr/local/include/glm/")
set(LIBRARY_INCLUDE_DIR_FREETYPE2 "/usr/include/freetype2/")
set(LIBRARY_INCLUDE_DIR_LIBJPEG "/usr/local/include/")
set(LIBRARY_INCLUDE_DIR_LIBPNG "/usr/include/libpng/")


###############################################
# GLUL (shared library) project
###############################################

project (GLUL_SHARED CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIBRARY_INCLUDE_DIR_GLFW})
include_directories(${LIBRARY_INCLUDE_DIR_GLEW})
include_directories(${LIBRARY_INCLUDE_DIR_GLM})
include_directories(${LIBRARY_INCLUDE_DIR_FREETYPE2})
include_directories(${LIBRARY_INCLUDE_DIR_LIBJPEG})
include_directories(${LIBRARY_INCLUDE_DIR_LIBPNG})

add_library(GLUL_SHARED SHARED 
    ${GLUL_SRCS} 
    ${GLUL_H}
)

target_link_libraries(GLUL_SHARED
    glfw            # GLFW3
    GLEW            # GLEW
    GL              # OpenGL
    freetype        # freetype2
    png             # libpng
    jpeg            # libjpeg
    z               # zlib
)

set_target_properties(GLUL_SHARED PROPERTIES 
    OUTPUT_NAME GLUL
)


###############################################
# GLUL (static library) project
###############################################

project (GLUL_Static CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIBRARY_INCLUDE_DIR_GLFW})
include_directories(${LIBRARY_INCLUDE_DIR_GLEW})
include_directories(${LIBRARY_INCLUDE_DIR_GLM})
include_directories(${LIBRARY_INCLUDE_DIR_FREETYPE2})
include_directories(${LIBRARY_INCLUDE_DIR_LIBJPEG})
include_directories(${LIBRARY_INCLUDE_DIR_LIBPNG})

add_library(GLUL_Static STATIC 
    ${GLUL_SRCS} 
    ${GLUL_H}
)

set_target_properties(GLUL_Static PROPERTIES 
    OUTPUT_NAME GLUL
)


###############################################
# Unit tests
###############################################

if(BUILD_TESTS)
    enable_testing()

    set(GLUL_Unit_Tests_SRCS
        "tests/src/main.cpp"
        
        "tests/src/GLUL/Clock.cpp"
        "tests/src/GLUL/File.cpp"
        "tests/src/GLUL/Image.cpp"
        "tests/src/GLUL/Line.cpp"
        "tests/src/GLUL/Point.cpp"
        "tests/src/GLUL/String.cpp"
    )

    set(GLUL_Unit_Tests_H
        
    )

    add_executable(GLUL_Unit_Tests 
        ${GLUL_Unit_Tests_SRCS}
        ${GLUL_Unit_Tests_H}
    )

    target_link_libraries(GLUL_Unit_Tests 
        gtest
        gtest_main
    )

    target_link_libraries(GLUL_Unit_Tests
        GLUL_SHARED
    )

    add_test(
        NAME GLUL_UnitTests 
        COMMAND GLUL_Unit_Tests
    )

    set_target_properties(GLUL_Unit_Tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "tests/bin/"
    )

endif()


###############################################
# Basic example project
###############################################

project (GLUL_Example_Basic CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_Basic_SRCS
    "examples/basic/src/main.cpp"
)

set(GLUL_Example_Basic_H
    
)

add_executable(GLUL_Example_Basic 
    ${GLUL_Example_Basic_SRCS}
    ${GLUL_Example_Basic_H}
)

target_link_libraries(GLUL_Example_Basic
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Basic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/basic/bin/"
)


###############################################
# Font example project
###############################################

project (GLUL_Example_Font CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_Font_SRCS
    "examples/font/src/main.cpp"
)

set(GLUL_Example_Font_H
    
)

add_executable(GLUL_Example_Font 
    ${GLUL_Example_Font_SRCS}
    ${GLUL_Example_Font_H}
)

target_link_libraries(GLUL_Example_Font
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Font PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/font/bin/"
)


###############################################
# Framework example project
###############################################

project (GLUL_Example_Framework CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_Framework_SRCS
    "examples/framework/src/main.cpp"
    "examples/framework/src/ExampleState.cpp"
)

set(GLUL_Example_Framework_H
    "examples/framework/src/ExampleState.h"
)

add_executable(GLUL_Example_Framework 
    ${GLUL_Example_Framework_SRCS}
    ${GLUL_Example_Framework_H}
)

target_link_libraries(GLUL_Example_Framework
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Framework PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/framework/bin/"
)


###############################################
# Image example project
###############################################

project (GLUL_Example_Image CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_Image_SRCS
    "examples/image/src/main.cpp"
)

set(GLUL_Example_Image_H
    "examples/models/src/InitializationState.h"
    "examples/models/src/WorkState.h"
)

add_executable(GLUL_Example_Image 
    ${GLUL_Example_Image_SRCS}
    ${GLUL_Example_Image_H}
)

target_link_libraries(GLUL_Example_Image
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Image PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/image/bin/"
)


###############################################
# Input example project
###############################################

project (GLUL_Example_Input CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build input example
set(GLUL_Example_Input_SRCS
    "examples/input/src/main.cpp"
)

set(GLUL_Example_Input_H
    
)

add_executable(GLUL_Example_Input 
    ${GLUL_Example_Input_SRCS}
    ${GLUL_Example_Input_H}
)

target_link_libraries(GLUL_Example_Input
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Input PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/input/bin/"
)


###############################################
# Models example project
###############################################

project (GLUL_Example_Models CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_Models_SRCS
    "examples/models/src/main.cpp"
    "examples/models/src/InitializationState.cpp"
    "examples/models/src/WorkState.cpp"
)

set(GLUL_Example_Models_H
    "examples/models/src/InitializationState.h"
    "examples/models/src/WorkState.h"
)

add_executable(GLUL_Example_Models 
    ${GLUL_Example_Models_SRCS}
    ${GLUL_Example_Models_H}
)

target_link_libraries(GLUL_Example_Models
    GLUL_SHARED
)

set_target_properties(GLUL_Example_Models PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/models/bin/"
)


###############################################
# GUI example project
###############################################

project (GLUL_Example_GUI CXX)

# Include directories paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# These files are to build basic example
set(GLUL_Example_GUI_SRCS
    "examples/gui/src/main.cpp"
)

set(GLUL_Example_GUI_H
    
)

add_executable(GLUL_Example_GUI 
    ${GLUL_Example_GUI_SRCS}
    ${GLUL_Example_GUI_H}
)

target_link_libraries(GLUL_Example_GUI
    GLUL_SHARED
)

set_target_properties(GLUL_Example_GUI PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "examples/gui/bin/"
)
