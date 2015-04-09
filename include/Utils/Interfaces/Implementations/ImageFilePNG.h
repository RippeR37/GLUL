#ifndef UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEPNG_H_INCLUDED
#define UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEPNG_H_INCLUDED

#include <Utils/Interfaces/ImageFile.h>

namespace Util {

    class ImageFilePNG : public Interface::ImageFile {
        public:
            Image read(const std::string& path) const throw(Util::Exception::InitializationFailed);
            void  save(const Image& image, const std::string& path) const throw(Util::Exception::InitializationFailed);
    };

}

#endif