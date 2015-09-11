#pragma once

#include <GLUL/Exception.h>


namespace GLUL {

    class GLUL_API Exception::InitializationFailed : public Exception {
        public:
            InitializationFailed() throw();
            InitializationFailed(const std::string& description) throw();

    };

}
