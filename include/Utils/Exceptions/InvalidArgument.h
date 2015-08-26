#ifndef UTILS_EXCEPTION_INVALIDARGUMENT_H_INCLUDED
#define UTILS_EXCEPTION_INVALIDARGUMENT_H_INCLUDED

#include <Utils/Exception.h>


namespace Util {

    class UTILS_API Exception::InvalidArgument : public Exception {
        public:
            InvalidArgument() throw();
            InvalidArgument(const std::string& description) throw();

    };

}

#endif
