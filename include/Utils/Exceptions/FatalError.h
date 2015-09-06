#ifndef UTILS_EXCEPTION_FATALERROR_H_INCLUDED
#define UTILS_EXCEPTION_FATALERROR_H_INCLUDED

#include <Utils/Exception.h>


namespace Util {

    class UTILS_API Exception::FatalError : public Exception {
        public:
            FatalError() throw();
            FatalError(const std::string& description) throw();

    };

}

#endif
