#include <Utils/Exception.h>

#include <iostream>

namespace Util {

    Exception::Exception() {
        _description = std::string("Exception thrown");
    }

    Exception::Exception(const std::string& description) {
        _description = description;
    }

    Exception::~Exception() {

    }

    void Exception::print() const {
        std::cerr << _description << std::endl;
    }

    const char* Exception::what() const {
        return _description.c_str();
    }

    const std::string& Exception::getDescription() const {
        return _description;
    }

}