#ifndef UTILS_IMAGE_H_INCLUDED
#define UTILS_IMAGE_H_INCLUDED

#include <Utils/Exception.h>

#include <glm/vec4.hpp>

#include <string>

namespace Util {

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

            void load(const std::string& path, Format format = Format::Auto) throw(Exception::InitializationFailed);
            void load(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data, bool isRGB = true);

            void reset();
            
            glm::uvec4 getPixel(unsigned int x, unsigned int y) const;

            unsigned int getBits() const;
            unsigned int getSize() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            unsigned char* getData() const;

        public:
            static void swapComponents(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) throw(Util::Exception::InvalidArgument);

        private:
            void loadBMP(const std::string& path) throw(Exception::InitializationFailed);
            void loadTGA(const std::string& path) throw(Exception::InitializationFailed);
            void loadJPG(const std::string& path) throw(Exception::InitializationFailed);
            void loadPNG(const std::string& path) throw(Exception::InitializationFailed);

            unsigned int _size;
            unsigned int _width;
            unsigned int _height;
            unsigned int _bits;
            unsigned char* _data;
    };

}

#endif