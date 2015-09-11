#include <GLUL/Exception.h>

#include <iostream>


namespace GLUL {

    Exception::Exception() throw() {
        _description = std::string("Exception thrown");
    }

    Exception::Exception(const std::string& description) throw() {
        _description = description;
    }

    Exception::~Exception() throw() {

    }

    void Exception::print() const {
        std::cerr << _description << std::endl;
    }

    const char* Exception::what() const throw() {
        return _description.c_str();
    }

    const std::string& Exception::getDescription() const throw() {
        return _description;
    }

}
