#ifndef UTILS_CONFIG_H_INCLUDED
#define UTILS_CONFIG_H_INCLUDED


    /**
     * Versions
     */
    #define UTILS_VERSION_MAJOR 0
    #define UTILS_VERSION_MINOR 2
    #define UTILS_VERSION_PATCH 0


    /**
     * Identify OS
     */
    #if defined(_WIN32)
        #define UTILS_OS_WINDOWS
    #elif defined(__APPLE__) && defined(__MACH__)
        #define UTILS_OS_OSX
    #elif defined(__unix__) && defined(__linux__)
        #define UTILS_OS_LINUX
    #else
        #error This operating system is not supported by this library.
    #endif


    /**
     * Portable import/export macros for DLL build targets
     */
    #if defined(UTILS_DLL)

        #if defined(UTILS_OS_WINDOWS)

            #define UTILS_API_EXPORT __declspec(dllexport)
            #define UTILS_API_IMPORT __declspec(dllimport)

            #ifdef _MSC_VER
                #pragma warning(disable: 4251)
            #endif

        #else

            #if __GNUC__ >= 4
                #define UTILS_API_EXPORT __attribute__ ((__visibility__ ("default")))
                #define UTILS_API_IMPORT __attribute__ ((__visibility__ ("default")))
            #else
                #define UTILS_API_EXPORT
                #define UTILS_API_IMPORT
            #endif

        #endif

    #else

        #define UTILS_API_EXPORT
        #define UTILS_API_IMPORT

    #endif


    /**
     * Define UTILS_API based on build target
     */
    #if defined(UTILS_EXPORTS)
        #define UTILS_API UTILS_API_EXPORT
    #else
        #define UTILS_API UTILS_API_IMPORT
    #endif


#endif
