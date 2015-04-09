#ifndef UTILS_INTERFACES_IMAGEFILE_H_INCLUDED
#define UTILS_INTERFACES_IMAGEFILE_H_INCLUDED

#include <Utils/Image.h>

namespace Util {

    namespace Interface {

        class ImageFile {
            public:
                ImageFile();
                virtual ~ImageFile();

                virtual Image read(const std::string& path) const throw(Util::Exception::InitializationFailed) = 0;
                virtual void  save(const std::string& path) const throw(Util::Exception::InitializationFailed) = 0;

            protected:
                void setImage(Image& image, unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) const;
        };

    }

}

#endif