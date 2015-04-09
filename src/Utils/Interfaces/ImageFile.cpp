#include <Utils/Interfaces/ImageFile.h>

namespace Util {

    namespace Interface {

        ImageFile::ImageFile() {
            
        }

        ImageFile::~ImageFile() {
            
        } 
        
        void ImageFile::setImage(Image& image, unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) const {
            image._width = width;
            image._height = height;
            image._bits = bits;
            image._size = width * height * (bits / 8);
            image._data = data;
        }

    }

}