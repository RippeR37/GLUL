## GLUL - OpenGL Utility Library

| Branch | Linux | Windows | Coverage | Download |
| :----: | :---: | :-----: | :------: | :------: |
| Master | [![Build Status](https://travis-ci.org/RippeR37/GLUL.svg?branch=master)](https://travis-ci.org/RippeR37/GLUL) | [![Build status](https://ci.appveyor.com/api/projects/status/950gw1wrdvxgx1j1/branch/master?svg=true)](https://ci.appveyor.com/project/RippeR37/glul/branch/master) | [![Coverage Status](https://coveralls.io/repos/RippeR37/GLUL/badge.svg?branch=master)](https://coveralls.io/github/RippeR37/GLUL?branch=master) | [ ![Download](https://api.bintray.com/packages/ripper37/generic/GLUL/images/download.svg) ](https://bintray.com/ripper37/generic/GLUL/_latestVersion#files) |
| Develop | [![Build Status](https://travis-ci.org/RippeR37/GLUL.svg?branch=develop)](https://travis-ci.org/RippeR37/GLUL) | [![Build status](https://ci.appveyor.com/api/projects/status/950gw1wrdvxgx1j1/branch/develop?svg=true)](https://ci.appveyor.com/project/RippeR37/glul/branch/develop) | [![Coverage Status](https://coveralls.io/repos/RippeR37/GLUL/badge.svg?branch=develop)](https://coveralls.io/github/RippeR37/GLUL?branch=develop) | [ ![Download](https://api.bintray.com/packages/ripper37/generic/GLUL/images/download.svg) ](https://bintray.com/ripper37/generic/GLUL/_latestVersion#files) |


### Main features
- Object-oriented wrapper for OpenGL functionality
    - provides type-safety using strongly typed enumerations
- Window creation and management
- Input management
    - Event based (with aggregators, handlers and triggers)
    - Keyboard support
    - Mouse support
- Interfaces to recurring elements to encourage using polymorphism, like:
    - cameras
    - states
    - models (i.e. 2D/3D models used by games/visualizations)
- Framework(s) to speed-up building small-to-medium applications and games
- Model loaders (i.e. OBJ model loader with full integration to library)
- Many usefull modules (e.g. timing, clocks, window managers) and algorithms, like:
    - logging module
    - operations on strings, files, etc.
    - collision detection
    - and others...
- GUI module
    - Component/container based
    - Extendable
    - Many handy events like onMouseEnter
    - Still work in progress
- Multiplatform support (tested on Windows, Linux and Mac OS)

Library strongly uses C++11 features like move constructors/assignment operators, lambdas, range-based loops, strongly typed pointers (with nullptr), strongly typed enumerations (_enum class_), hash maps etc. when it's clear much would be gained by it.

### Modules
- OpenGL Wrapper
    - Buffers
        - VertexBuffers
    - Contexts
    - Matrix stacks
    - Model storage and manipulation
        - Materials
        - Meshes
        - OBJ loader
    - Pipelines
    - Programs
        - Shaders
    - Textures
    - Uniforms
    - Vertex arrays
        - Vertex attributes
- GUI Module
    - Components
        - Text/label
    - Containers
    - Font loader (TrueType)
- Exceptions
    - FatalError
    - InitializationFailed
    - InvalidArgument
- Frameworks
    - State flow application framework
    - _Interfaces for MVC framework elements_
- Helpers
    - HashEnum
- Input
    - Event
        - KeyEvent
        - MouseButtonEvent
        - MouseMovementEvent
        - MouseScrollEvent
    - EventAggregator
    - EventHandler
    - EventTrigger
    - Keyboard (direct queries)
    - Mouse (direct queries)
    - Types (types definitions)
- Interfaces
    - Cameras
    - Models (2D/3D models)
    - States
    - ImageFile (r/w interface on files for Image class)
- AABB
- Time
    - Clocks
    - Timed events
    - Time loops
        - fixed
        - semi-fixed
        - variable
    - Timers
- Exceptions
- Files
- Images
    - BMP (read & write)
    - TGA (read & write)
    - JPEG (read)
    - PNG (read)
- Data types
    - Lines
    - Points
    - Rectangles
    - Boxes (through AABB)
- String manipulation
- Window management
    - Window
    - GUI Window
    - Windows (window registering, retrieving and management)


Documentation for each module should be created soon.

### Requirements
- C++11 supporting compiler (project for Visual Studio 2013 provided)

### Platforms tested
- Windows (tested on Windows 7 x64)
- Linux (tested on Ubuntu 14.04)
- Mac OS (tested by user(s))

### Compilers tested
- MSVC (tested on Visual Studio 2013)
- GCC (tested on 5.1.0)
- Clang 3.6

### Dependencies
- [GLFW](http://www.glfw.org/) (tested on 3.1)
- [GLEW](http://www.glew.sourceforge.net/) (tested on 1.13.0)
- [GLM](http://www.glm.g-truc.net/) (tested on 0.9.5.4)
- [FT2](http://www.freetype.org/freetype2/) (tested on 2.5.5)
- [libJPEG](http://www.ijg.org/) ([tested](https://beeproc.wordpress.com/2012/11/18/building-libjpeg-8d-with-msvc-2012/) on 9a, [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) might also work)
- [libPNG](http://www.libpng.org/pub/png/libpng.html) (tested on 1.6.17)
- [zlib](http://www.zlib.net/) (tested on 1.2.8, libPNG's dependency)

### License
See [LICENSE](LICENSE) file.

### Examples of usage
You can find examples of this library's usage in `example` directory or [here](https://github.com/RippeR37/GLUL/wiki/ExampleProjects).

### Author
Most of the code is written completly by me. Some parts may be inspired by publicly shared code on websites like Stack Overflow. Unfortunatly that code traveled with me between projects for so long that i cannot remember every detail. I would happily mention you here though, so please inform me of any usage of your work.

## Help with library
Feel free to fork library (leaving details about author) and work on it with me. Issue list should be up to date on what is to do and what is to fix. If you'd like to see new features or functionality please contact me and i'll do my best.
