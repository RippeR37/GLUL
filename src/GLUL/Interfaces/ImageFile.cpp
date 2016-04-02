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

        std::vector<unsigned char> ImageFile::getRGBDataOf(const Image& image) const {
            std::vector<unsigned char> result;

            result.reserve(image.getWidth() * image.getHeight() * 3);

            for(int row = 0; row < image.getHeight(); ++row) {
                for(int coll = 0; coll < image.getWidth(); ++coll) {
                    glm::uvec4 pixel = image.getPixel(coll, row);

                    result.push_back(static_cast<unsigned char>(pixel.r));
                    result.push_back(static_cast<unsigned char>(pixel.g));
                    result.push_back(static_cast<unsigned char>(pixel.b));
                }
            }

            return result;
        }

    }

}