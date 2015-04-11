## Utility-Library
Utility library to simplify using OpenGL written in C++11.   

Library provides:
- Object-oriented wrapper for OpenGL functionality
    - provides type-safety using strongly typed enumerations
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
- _GUI module (**yet to be finished**)_

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
- Frameworks
    - State flow application framework
    - _Interfaces for MVC framework elements_
- Interfaces
    - Cameras
    - Models (2D/3D models)
    - States
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
- Windows

Documentation for each module should be created soon.

### Requirements
- C++11 supporting compiler (project for Visual Studio 2013 provided)

### Dependencies
- [GLFW](http://www.glfw.org/) (tested on 3.1)
- [GLEW](http://www.glew.sourceforge.net/) (tested on 1.12.0)
- [GLM](http://www.glm.g-truc.net/) (tested on 0.9.5.4)
- [FT2](http://www.freetype.org/freetype2/) (tested on 2.5.5)
- [libJPEG](http://www.ijg.org/) ([tested](https://beeproc.wordpress.com/2012/11/18/building-libjpeg-8d-with-msvc-2012/) on 9a, [libjpeg-turbo](http://libjpeg-turbo.virtualgl.org/) might also work)
- [libPNG](http://www.libpng.org/pub/png/libpng.html) (tested on 1.6.17)
- [zlib](http://www.zlib.net/) (tested on 1.2.8, libPNG's dependency)

### License
[GNU GPLv2](LICENSE).

### Examples of usage
You can find examples of this library's usage in `example` directory or [here](https://github.com/RippeR37/Utility-Library/wiki/ExampleProjects).

### Author
Most of the code is written completly by me. Some parts may be inspired by publicly shared code on websites like Stack Overflow. Unfortunatly that code traveled with me between projects for so long that i cannot remember every detail. I would happily mention you here though, so please inform me of any usage of your work.

## Help with library
Feel free to fork library (leaving details about author) and work on it with me. Issue list should be up to date on what is to do and what is to fix. If you'd like to see new features or functionality please contact me and i'll do my best.
