#pragma once

#include <GLUL/Exception.h>


namespace GLUL {

    class GLUL_API Exception::InvalidArgument : public Exception {
        public:
            InvalidArgument() throw();
            InvalidArgument(const std::string& description) throw();

    };

}
