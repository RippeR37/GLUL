#include <GLUL/Exceptions/FatalError.h>


namespace GLUL {

    Exception::FatalError::FatalError() throw() {
        _description = std::string("Fatal error has occured");
    }

    Exception::FatalError::FatalError(const std::string& description) throw() {
        _description = description;
    }

}
