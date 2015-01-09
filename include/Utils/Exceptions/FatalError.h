#ifndef UTIL_EXCEPTION_FATALERROR_H_INCLUDED
#define UTIL_EXCEPTION_FATALERROR_H_INCLUDED

#include "../Exception.h"

namespace Util {

    class Exception::FatalError : public Exception {
        public:
            Exception::FatalError() throw();
            Exception::FatalError(const std::string& description) throw();

    };

}

#endif