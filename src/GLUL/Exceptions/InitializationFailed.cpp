#include <GLUL/Exceptions/InitializationFailed.h>


namespace GLUL {

    Exception::InitializationFailed::InitializationFailed() throw() {
        _description = std::string("Initialization has failed");
    }

    Exception::InitializationFailed::InitializationFailed(const std::string& description) throw() {
        _description = description;
    }

}
