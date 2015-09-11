#pragma once

#include <GLUL/Config.h>

#include <string>
#include <fstream>
#include <unordered_map>


namespace GLUL {

    class GLUL_API Logger {
        public:
            class GLUL_API LoggerStream {
                public:
                    void operator<<(const std::string& message);
                    void log(const std::string& message);
                    void logError(const std::string& errorMessage);
                    void logWarning(const std::string& warningMessage);
                    
                private:
                    LoggerStream();
                    LoggerStream(const LoggerStream&) = delete;
                    ~LoggerStream();

                    bool open();
                    void close();

                    void setName(const std::string& name);
                    void setPath(const std::string& path);

                    std::ofstream& getStream();

                    std::string _name;
                    std::string _path;
                    std::ofstream _stream;

                public:
                    friend class Logger;
                    friend struct std::pair<const std::string, LoggerStream>;
            };


        public:
            static LoggerStream& Stream(const std::string& streamName, const std::string& streamPath);
            static LoggerStream& Stream(const std::string& streamName);

            static LoggerStream& LibraryStream();

        private:
            Logger();
            Logger(const Logger&) = delete;
            ~Logger();
            
            Logger& operator=(const Logger&) = delete;

            static Logger& getInstance();

            std::unordered_map<std::string, LoggerStream> _streams;
    };

    typedef Logger Log;

}
