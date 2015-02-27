#ifndef UTILS_IMAGE_H_INCLUDED
#define UTILS_IMAGE_H_INCLUDED

#include <string>

namespace Util {

    class Image {
        public:
            enum class Format {
                BMP,
                TGA,
                // JPG,
                // PNG,
                Auto,
            };

        public:
            Image(const std::string& path, Format format = Format::Auto);
            Image(const Image& image);
            Image(Image&& image);
            ~Image();

            unsigned int getBits() const;
            unsigned int getSize() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            unsigned char* getData() const;

        private:
            void loadBMP(const std::string& path);
            void loadTGA(const std::string& path);

            unsigned int _size;
            unsigned int _width;
            unsigned int _height;
            unsigned int _bits;
            unsigned char* _data;
    };

}

#endif