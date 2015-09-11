#pragma once

#include <GLUL/Interfaces/ImageFile.h>


namespace GLUL {

    namespace Interface {
    
        class GLUL_API ImageFilePNG : public Interface::ImageFile {
            public:
                Image read(const std::string& path) const throw(GLUL::Exception::InitializationFailed);
                void  save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed);
        };

    }
}
