#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Exception.h>

#include <string>


namespace Util {

    class UTILS_API File {
        public:

        public:
            static bool exists(const std::string& path);

            static std::string readText(const std::string& path, bool throwException = false) throw(Exception::FatalError);

            static std::string getPath(const std::string& path);
            static std::string getFilename(const std::string& path);
            static std::string getFilenameExtensionless(const std::string& path);
            static std::string getExtension(const std::string& path);
    };

}

#endif
