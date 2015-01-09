#include <Utils/File.h>

namespace Util {

    std::string File::read(std::string path, ReadMode mode, bool throwException) {
        std::ifstream fileStream;
        std::string result = "";
        std::string line   = "";

        fileStream.open(path, std::fstream::in | mode);
        if(fileStream.is_open()) {
            while(std::getline(fileStream, line))
                result += "\n" + line;
            fileStream.close();
        } else if(throwException) {
            std::string errorMsg = "Could not open file: '" + path + "'";
            throw Exception::FatalError(errorMsg.c_str());
        }

        return result;
    }

    std::string File::getPath(std::string filePath) {
        return filePath.substr(0, filePath.find_last_of("/\\"));
    }

    std::string File::getFilename(std::string filePath) {
        return filePath.substr(filePath.find_last_of("/\\") + 1);
    }

    std::string File::getFilenameExtensionless(std::string filePath) {
        std::string fileName = File::getFilename(filePath);

        return fileName.substr(0, fileName.find_last_of("."));
    }

    std::string File::getExtension(std::string filePath) {
        return filePath.substr(filePath.find_last_of(".") + 1);
    }

}