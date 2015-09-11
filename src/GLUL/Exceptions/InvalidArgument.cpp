#include <GLUL/Exceptions/InvalidArgument.h>


namespace GLUL {

    Exception::InvalidArgument::InvalidArgument() throw() {
        _description = std::string("Invalid argument provided");
    }

    Exception::InvalidArgument::InvalidArgument(const std::string& description) throw() {
        _description = description;
    }

}
