#pragma once


/**
 * Versions
 */
#define GLUL_VERSION_MAJOR 0
#define GLUL_VERSION_MINOR 2
#define GLUL_VERSION_PATCH 0


/**
 * Identify OS
 */
#if defined(_WIN32)
    #define GLUL_OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define GLUL_OS_OSX
#elif defined(__unix__) && defined(__linux__)
    #define GLUL_OS_LINUX
#else
    #error This operating system is not supported by this library.
#endif


/**
 * Portable import/export macros for DLL build targets
 */
#if defined(GLUL_DLL)

    #if defined(GLUL_OS_WINDOWS)

        #define GLUL_API_EXPORT __declspec(dllexport)
        #define GLUL_API_IMPORT __declspec(dllimport)

        #ifdef _MSC_VER
            #pragma warning(disable: 4251)
        #endif

    #else

        #if __GNUC__ >= 4
            #define GLUL_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define GLUL_API_IMPORT __attribute__ ((__visibility__ ("default")))
        #else
            #define GLUL_API_EXPORT
            #define GLUL_API_IMPORT
        #endif

    #endif

#else

    #define GLUL_API_EXPORT
    #define GLUL_API_IMPORT

#endif


/**
 * Define GLUL_API based on build target
 */
#if defined(GLUL_EXPORT)
    #define GLUL_API GLUL_API_EXPORT
#else
    #define GLUL_API GLUL_API_IMPORT
#endif
