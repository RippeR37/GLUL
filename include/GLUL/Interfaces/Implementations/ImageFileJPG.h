#pragma once

#include <GLUL/Interfaces/ImageFile.h>


namespace GLUL {

    namespace Interface {

        class GLUL_API ImageFileJPG : public Interface::ImageFile {
            public:
                ImageFileJPG(); // uses defaultQuality value
                ImageFileJPG(int quality);

                Image read(const std::string& path) const throw(GLUL::Exception::InitializationFailed);
                void  save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed);

                static int defaultQuality;

            private:
                int _quality;
        };

    }

}
