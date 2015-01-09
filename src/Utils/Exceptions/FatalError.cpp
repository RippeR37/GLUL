#include <Utils/Exceptions/FatalError.h>

namespace Util {

    Exception::FatalError::FatalError() {
        _description = std::string("Fatal error has occured");
    }

    Exception::FatalError::FatalError(const std::string& description) {
        _description = description;
    }

}