#ifndef UTILS_EXCEPTION_INITIALIZATIONFAILED_H_INCLUDED
#define UTILS_EXCEPTION_INITIALIZATIONFAILED_H_INCLUDED

#include <Utils/Exception.h>

namespace Util {

    class Exception::InitializationFailed : public Exception {
        public:
            InitializationFailed() throw();
            InitializationFailed(const std::string& description) throw();

    };

}

#endif