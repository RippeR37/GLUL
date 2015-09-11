#pragma once

#include <GLUL/Config.h>
#include <GLUL/Exception.h>

#include <glm/vec4.hpp>

#include <string>


namespace GLUL {

    namespace Interface {
        class ImageFile; // Interface for reading and writing image files
    }

    class GLUL_API Image {
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
            void load(const std::string& path, const Interface::ImageFile& fileInterface) throw(Exception::InitializationFailed);
            void load(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data, bool isRGB = true);

            void save(const std::string& path, Format format = Format::Auto) throw(Exception::InitializationFailed);
            void save(const std::string& path, const Interface::ImageFile& fileInterface) throw(Exception::InitializationFailed);

            void reset() throw();

            // algorithms
            void crop(const glm::uvec2& origin, const glm::uvec2& size);

            void rotate90CW();
            void rotate90CCW();
            void rotate180();

            void invertHorizontal();
            void invertVertical();

            void invertColors();
            void toGrayscale(float percentage = 1.0f);


            // getters
            unsigned int getBits() const;
            unsigned int getSize() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            unsigned char* getData() const;
            glm::uvec4 getPixel(unsigned int x, unsigned int y) const;

            // setter
            void setPixel(unsigned int x, unsigned int y, const glm::uvec4& color);

        public:
            static void swapComponents(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) throw(GLUL::Exception::InvalidArgument);

            static unsigned int getAlignedRowSize(unsigned int width, unsigned int bits);

        private:
            unsigned int _size;
            unsigned int _width;
            unsigned int _height;
            unsigned int _bits;
            unsigned char* _data;

        public:
            friend class GLUL::Interface::ImageFile;
    };

}
