#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include <Utils/Exception.h>

#include <string>
#include <fstream>

namespace Util {

    class File {
        public:
            enum ReadMode {
                Text   = 0,
                Binary = std::fstream::binary, 
            };

        public:
            static std::string read(std::string path, ReadMode mode = ReadMode::Text, bool throwException = false)
                throw(Exception::FatalError);

            static std::string getPath(std::string filePath);
            static std::string getFilename(std::string filePath);
            static std::string getFilenameExtensionless(std::string filePath);
            static std::string getExtension(std::string filePath);

        private:

    };

}

#endif