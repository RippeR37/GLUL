#ifndef UTILS_LOGGER_H_INCLUDED
#define UTILS_LOGGER_H_INCLUDED

#include <string>
#include <fstream>
#include <unordered_map>

namespace Util {

    class Logger {
        public:
            class LoggerStream {
                public:
                    void operator<<(const std::string& message);
                    void log(const std::string& message);
                    
                private:
                    LoggerStream();
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
                    friend class Util::Logger;
                    friend struct std::pair<const std::string, LoggerStream>;
            };

        public:
            static LoggerStream& Stream(const std::string& streamName, const std::string& streamPath);
            static LoggerStream& Stream(const std::string& streamName);

        private:
            Logger();
            ~Logger();

            static std::unordered_map<std::string, LoggerStream> _streams;
    };

    typedef Logger Log;

}

#endif