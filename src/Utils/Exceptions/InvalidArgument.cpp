#include <Utils/Exceptions/InvalidArgument.h>

namespace Util {

    Exception::InvalidArgument::InvalidArgument() throw() {
        _description = std::string("Invalid argument provided");
    }

    Exception::InvalidArgument::InvalidArgument(const std::string& description) throw() {
        _description = description;
    }

}