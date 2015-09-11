#include <GLUL/Interfaces/ImageFile.h>

namespace GLUL {

    namespace Interface {

        ImageFile::ImageFile() {
            
        }

        ImageFile::~ImageFile() {
            
        } 
        
        void ImageFile::setImage(Image& image, unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) const {
            unsigned int rowStride;

            image._width = width;
            image._height = height;
            image._bits = bits;
            image._data = data;
            
            rowStride = width * (bits / 8);
            rowStride = rowStride + (3 - ((rowStride - 1) % 4));

            image._size = height * rowStride;
        }

    }

}