#include <Utils/File.h>

namespace Util {

    std::string File::read(const std::string& path, ReadMode mode, bool throwException) {
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

    bool File::exists(const std::string& path) {
        bool result;
        std::ifstream file(path.c_str());

        result = file.good();
        
        return result;
    }

    std::string File::getPath(const std::string& path) {
        std::string result;
        
        result = path.substr(0, path.find_last_of("/\\"));
        
        return result;
    }

    std::string File::getFilename(const std::string& path) {
        std::string result;

        result = path.substr(path.find_last_of("/\\") + 1);

        return result;
    }

    std::string File::getFilenameExtensionless(const std::string& path) {
        std::string result;
        std::string fileName = File::getFilename(path);

        result = fileName.substr(0, fileName.find_last_of("."));
        
        return result;
    }

    std::string File::getExtension(const std::string& filePath) {
        std::string result;

        result = filePath.substr(filePath.find_last_of(".") + 1);
        
        return result;
    }

}