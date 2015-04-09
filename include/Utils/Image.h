#ifndef UTILS_IMAGE_H_INCLUDED
#define UTILS_IMAGE_H_INCLUDED

#include <Utils/Exception.h>

#include <glm/vec4.hpp>

#include <string>

namespace Util {

    namespace Interface {
        class ImageFile; // Interface for reading and writing image files
    }

    class Image {
        public:
            enum class Format {
                BMP,
                TGA,
                JPG,
                PNG,
                Auto,
            };

        public:
            Image() throw();
            Image(const std::string& path, Format format = Format::Auto) throw(Exception::InitializationFailed);
            Image(const Image& image) throw();
            Image(Image&& image) throw();
            ~Image();

            Image& operator=(const Image& image);
            Image& operator=(Image&& image);

            void load(const std::string& path, Format format = Format::Auto) throw(Exception::InitializationFailed);
            void load(const std::string& path, const Interface::ImageFile& fileInterface);
            void load(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data, bool isRGB = true);

            void reset();

            unsigned int getBits() const;
            unsigned int getSize() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            unsigned char* getData() const;
            glm::uvec4 getPixel(unsigned int x, unsigned int y) const;

        public:
            static void swapComponents(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) throw(Util::Exception::InvalidArgument);

        private:
            unsigned int _size;
            unsigned int _width;
            unsigned int _height;
            unsigned int _bits;
            unsigned char* _data;

        public:
            friend class Util::Interface::ImageFile;
    };

}

#endif