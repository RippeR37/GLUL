#pragma once

#include <GLUL/Config.h>
#include <GLUL/Image.h>


namespace GLUL {

    namespace Interface {

        class GLUL_API ImageFile {
            public:
                ImageFile();
                virtual ~ImageFile();

                virtual Image read(const std::string& path) const throw(GLUL::Exception::InitializationFailed) = 0;
                virtual void  save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed) = 0;

            protected:
                void setImage(Image& image, unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) const;
        };

    }

}
