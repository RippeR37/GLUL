#include <Utils/Logger.h>

#include <iomanip>
#include <chrono>
#include <ctime>

namespace Util {

    std::unordered_map<std::string, Logger::LoggerStream> Logger::_streams;

    Logger::~Logger() {
        for(auto& stream : _streams)
            stream.second.close();
    }

    Logger::LoggerStream& Logger::Stream(const std::string& streamName, const std::string& streamPath) {
        _streams.erase(streamName);

        _streams[streamName].setName(streamName);
        _streams[streamName].setPath(streamPath);
        _streams[streamName].open();

        return Stream(streamName);
    }

    Logger::LoggerStream& Logger::Stream(const std::string& streamName) {
        if(_streams.count(streamName))
            return _streams[streamName];
        else
            return _streams["Default"];
    }


    /***
        LoggerStream's implementation
    ***/

    Logger::LoggerStream::LoggerStream() {

    }

    Logger::LoggerStream::~LoggerStream() {
        close();
    }

    void Logger::LoggerStream::operator<<(const std::string& message) {
        log(message);
    }

    void Logger::LoggerStream::log(const std::string& message) {
        if(_name == "" || _path == "" || _stream.is_open() == false) {
            _name = "Default";
            _path = "logs/default.log";
            _stream.open(_path, std::ofstream::trunc);
        }

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        _stream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X\t");
        _stream << message;
        _stream << std::endl;
    }


    void Logger::LoggerStream::logError(const std::string& errorMessage) {
        log(std::string("[Error]: ") + errorMessage);
    }

    void Logger::LoggerStream::logWarning(const std::string& warningMessage) {
        log(std::string("[Warning]: ") + warningMessage);
    }

    bool Logger::LoggerStream::open() {
        if(_path != "")
            _stream.open(_path, std::ofstream::trunc);

        return _stream.is_open();
    }

    void Logger::LoggerStream::close() {
        if(_stream.is_open())
            _stream.close();
    }

    void Logger::LoggerStream::setName(const std::string& name) {
        _name = name;
    }

    void Logger::LoggerStream::setPath(const std::string& path) {
        _path = path;
    }

    std::ofstream& Logger::LoggerStream::getStream() {
        return _stream;
    }


}