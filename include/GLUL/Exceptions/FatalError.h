#pragma once

#include <GLUL/Exception.h>


namespace GLUL {

    class GLUL_API Exception::FatalError : public Exception {
        public:
            FatalError() throw();
            FatalError(const std::string& description) throw();

    };

}
