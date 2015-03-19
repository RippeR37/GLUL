#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include <Utils/Exception.h>

#include <string>
#include <fstream>

namespace Util {

    class File {
        public:
            enum class ReadMode {
                Text   = 0,
                Binary = std::fstream::binary, 
            };

        public:
            static std::string read(const std::string& path, ReadMode mode = ReadMode::Text, bool throwException = false)
                throw(Exception::FatalError);

            static bool exists(const std::string& path);
            static std::string getPath(const std::string& path);
            static std::string getFilename(const std::string& path);
            static std::string getFilenameExtensionless(const std::string& path);
            static std::string getExtension(const std::string& path);

        private:

    };

}

#endif