#include <Utils/Exceptions/InitializationFailed.h>

namespace Util {

    Exception::InitializationFailed::InitializationFailed() throw() {
        _description = std::string("Initialization has failed");
    }

    Exception::InitializationFailed::InitializationFailed(const std::string& description) throw() {
        _description = description;
    }

}