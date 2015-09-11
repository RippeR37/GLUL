#include <GLUL/File.h>
#include <GLUL/Logger.h>

#include <fstream>


namespace GLUL {
    
    bool File::exists(const std::string& path) {
        bool result;
        std::ifstream file(path.c_str());

        result = file.good();
        
        return result;
    }

    std::string File::readText(const std::string& path, bool throwException) throw(GLUL::Exception::FatalError) {
        std::ifstream fileStream;
        std::string result = "";
        std::string line   = "";

        fileStream.open(path, std::fstream::in);
        if(fileStream.is_open()) {
            while(std::getline(fileStream, line)) {
                result += line;

                if(fileStream.eof() == false) {
                    result += "\n";
                }
            }

            fileStream.close();
        } else {
            GLUL::Log::LibraryStream().logError("Could not open file: '" + path + "'");

            if(throwException) {
                std::string errorMsg = "Could not open file: '" + path + "'";
                throw Exception::FatalError(errorMsg.c_str());
            }
        }

        return result;
    }

    std::string File::getPath(const std::string& path) {
        std::string result;
        
        result = path.substr(0, path.find_last_of("/\\") + 1);
        
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
