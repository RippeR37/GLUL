#ifndef UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEBMP_H_INCLUDED
#define UTILS_INTERFACES_IMPLEMENTATIONS_IMAGEFILEBMP_H_INCLUDED

#include <Utils/Interfaces/ImageFile.h>

namespace Util {

    namespace Interface {

        class ImageFileBMP : public Interface::ImageFile {
            private:
                struct BMPheader {
                    unsigned char bmpID[4]; // xxBM where xx is skipped due to alignment
                    unsigned int fileSize;
                    unsigned short reserved[2]; // not used
                    unsigned int dataOffset;

                    unsigned int headerSize; // BITMAPINFOHEADER = 40
                    unsigned int width; 
                    unsigned int height;
                    unsigned short planes; // 1
                    unsigned short bpp;
                    unsigned int compression;
                    unsigned int imageSize;
                    unsigned int xPelsPerMeter;
                    unsigned int yPelsPerMeter;
                    unsigned int clrUsed;
                    unsigned int clrImportantRotateAndReserved;
                };

            public:
                Image read(const std::string& path) const throw(Util::Exception::InitializationFailed);
                void  save(const Image& image, const std::string& path) const throw(Util::Exception::InitializationFailed);
        };

    }

}

#endif