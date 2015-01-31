#ifndef UTILS_IMAGE_H_INCLUDED
#define UTILS_IMAGE_H_INCLUDED

#include "Exception.h"

#include <string>

namespace Util {

    class Image {
        public:
            enum Format {
                BMP,
                // TGA,
                // JPG,
                // PNG,
                // AUTO,
            };

        public:
            Image(std::string path, Image::Format format);
            Image(const Image& image);
            Image(Image&& image);
            ~Image();

            unsigned int getBits() const;
            unsigned int getSize() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            unsigned char* getData() const;

        private:
            void loadBMP(const std::string& path) throw(Exception::FatalError);
            
            unsigned int _size;
            unsigned int _width;
            unsigned int _height;
            unsigned int _bits;
            unsigned char* _data;
    };

}

#endif