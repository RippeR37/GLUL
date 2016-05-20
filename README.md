## GLUL - OpenGL Utility Library

| Branch | Linux | Windows | Coverage | Download |
| :----: | :---: | :-----: | :------: | :------: |
| Master | [![Build Status](https://travis-ci.org/RippeR37/GLUL.svg?branch=master)](https://travis-ci.org/RippeR37/GLUL) | [![Build status](https://ci.appveyor.com/api/projects/status/950gw1wrdvxgx1j1/branch/master?svg=true)](https://ci.appveyor.com/project/RippeR37/glul/branch/master) | [![Coverage Status](https://coveralls.io/repos/RippeR37/GLUL/badge.svg?branch=master)](https://coveralls.io/github/RippeR37/GLUL?branch=master) | [ ![Download](https://api.bintray.com/packages/ripper37/generic/GLUL/images/download.svg) ](https://bintray.com/ripper37/generic/GLUL/_latestVersion#files) |
| Develop | [![Build Status](https://travis-ci.org/RippeR37/GLUL.svg?branch=develop)](https://travis-ci.org/RippeR37/GLUL) | [![Build status](https://ci.appveyor.com/api/projects/status/950gw1wrdvxgx1j1/branch/develop?svg=true)](https://ci.appveyor.com/project/RippeR37/glul/branch/develop) | [![Coverage Status](https://coveralls.io/repos/RippeR37/GLUL/badge.svg?branch=develop)](https://coveralls.io/github/RippeR37/GLUL?branch=develop) | [ ![Download](https://api.bintray.com/packages/ripper37/generic/GLUL/images/download.svg) ](https://bintray.com/ripper37/generic/GLUL/_latestVersion#files) |

<br>
**Modern C++ library** to speed-up working on **OpenGL** based applications and games.


### Main features
- **Modern OpenGL object-oriented wrapper**
    - type safety with strongly typed enumerations
    - no more resource leaks thanks to RAII
    - grouped functionality for ease of use
    - **low-level access to OpenGL functionality**
    - **high-level abstractions to common usage patterns**
- Window creation and management
    - multiple window support (through _GLFW3_)
- **Input management**
    - direct access to state of IO devices (Keyboard, Mouse, etc.)
    - event based abstractions
        - event aggregators, handlers and triggers
- Framework(s) to speed-up building small-to-medium applications and games
- Model loaders (e.g. OBJ model loader with full integration to library)
- Many small usefull modules like:
    - clock module to measure performance/time
    - logging module (with custom streams)
    - image module
        - support for BMP, TGA, JPEG and PNG images
        - both read and write for most popular formats
    - operations on strings, files, timers, time loops, etc.
    - and others...
- **2D graphics module** (\* in progress)
    - most popular primitives and shapes
        - Points, Lines, Triangles, Quads, Circles, Rings, and so on...
        - Sprites
        - Text rendering
            - dynamic fonts (through FreeType2)
    - easly extendible
    - very good performance
        - modern OpenGL (VAOs, VBOs etc.)
        - geometry batching (all geometry drawn in one call\*)
- **GUI module** (\* in progress)
    - component/container architecture
    - easly extendable
    - many built-in widgets
        - buttons, checkboxes, input fields, sliders, progress bars etc.
        - more on its way, and it's very easy to write new ones
    - many handy events like onMouseEnter, onMouseClick, onValueChange etc.
- **Cross-platform support**
    - Windows
    - Linux
    - Mac OS


Library strongly uses C++11 features like move constructors/assignment operators, lambdas, range-based loops, strongly typed pointers (with nullptr), strongly typed enumerations (_enum class_), hash maps etc. when it's clear much would be gained by it.


## Building

### Windows

* Clone this repository
* Download and configure all neccesary [dependencies](https://github.com/RippeR37/GLUL/#dependencies)
    * Script provided in `scripts\windows\install_msvc_dependencies.bat`
* Build library (and examples/tests) using provided:
    * Visual Studio 2013 project
    * CMake script

### Linux

* Clone this repository
* Download and configure all neccesary [dependencies](https://github.com/RippeR37/GLUL/#dependencies)
    * Script provided in `scripts\linux\install_dependencies.sh`
* Build library (and examples/tests) using provided CMake script


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


## Examples of usage
You can find provided example projects showcasing library's usage in `example` directory or you can check out [other projects which uses this library](https://github.com/RippeR37/GLUL/wiki/ExampleProjects).

Provided examples:

* Basic example (window creation and basic OpenGL usage)
* Font example (basic text rendering and internal font processing demo)
* Framework example (simple demo showing off basic framework for simple applications)
* **GUI example** (showcase of GUI module - built in widgets, events etc.)
* Image example (loading and saving of images, taking whole-window screenshots etc.)
* Input demo (showing IO module - how to use it in many different ways)
* Models demo (OBJ model loader with Phong shaders)


## License
This project is licensed under the [MIT License](LICENSE).


## Contributions
Feel free to fork library (leaving details about author) and work on it with me. Issue list should be up to date on what is to do and what is to fix. If you'd like to see new features or functionality please contact me or add new issue and i'll do my best.
