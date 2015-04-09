#ifndef UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEBMP_H_INCLUDED
#define UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEBMP_H_INCLUDED

#include <Utils/Interfaces/ImageFile.h>

namespace Util {

    class ImageFileBMP : public Interface::ImageFile {
        public:
            Image read(const std::string& path) const throw(Util::Exception::InitializationFailed);
            void  save(const std::string& path) const throw(Util::Exception::InitializationFailed);
    };

}

#endif