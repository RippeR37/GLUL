#include <GLUL/Image.h>
#include <GLUL/File.h>
#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFileBMP.h>
#include <GLUL/Interfaces/Implementations/ImageFileTGA.h>
#include <GLUL/Interfaces/Implementations/ImageFileJPG.h>
#include <GLUL/Interfaces/Implementations/ImageFilePNG.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <algorithm>
#include <cstdio>
#include <climits>
#include <fstream>
#include <iterator>
#include <cstring>


namespace GLUL {

    Image::Image() throw() {
        _data = nullptr;

        reset();
    }

    Image::Image(const std::string& path, Format format) throw(Exception::InitializationFailed) {
        _data = nullptr;

        load(path, format);
    }

    Image::Image(const Image& image) throw() {
        _size   = image._size;
        _width  = image._width;
        _height = image._height;
        _bits   = image._bits;
        _data   = nullptr;

        if(image._data != nullptr) {
            _data = new unsigned char[_size];

            std::copy(image._data, image._data + image._size, _data);
        }
    }

    Image::Image(Image&& image) throw() :
        _size(std::move(image._size)),
        _width(std::move(image._width)),
        _height(std::move(image._height)),
        _bits(std::move(image._bits)),
        _data(std::move(image._data))
    {
        image._data = nullptr;
        image.reset();
    }

    Image::~Image() {
        reset();
    }
    
    Image& Image::operator=(const Image& image) {
        _size = image._size;
        _width = image._width;
        _height = image._height;
        _bits = image._bits;

        if(image._data != nullptr && _size > 0) {
            _data = new unsigned char[_size];
            std::memcpy(_data, image._data, _size);
        }

        return *this;
    }

    Image& Image::operator=(Image&& image) {
        _size = image._size;
        _width = image._width;
        _height = image._height;
        _bits = image._bits;
        _data = image._data;

        image._size = 0;
        image._width = 0;
        image._height = 0;
        image._bits = 0;
        image._data = nullptr;

        return *this;
    }

    void Image::load(const std::string& path, Format format) throw(Exception::InitializationFailed) {
        switch(format) {
            case Format::BMP: load(path, GLUL::Interface::ImageFileBMP()); break;
            case Format::TGA: load(path, GLUL::Interface::ImageFileTGA()); break;
            case Format::JPG: load(path, GLUL::Interface::ImageFileJPG()); break;
            case Format::PNG: load(path, GLUL::Interface::ImageFilePNG()); break;

            default:
                std::string extension = GLUL::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP") {
                    load(path, GLUL::Interface::ImageFileBMP());
                } else if(extension == "tga" || extension == "TGA") {
                    load(path, GLUL::Interface::ImageFileTGA());
                } else if(extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG") {
                    load(path, GLUL::Interface::ImageFileJPG());
                } else if(extension == "png" || extension == "PNG") {
                    load(path, GLUL::Interface::ImageFilePNG());
                } else {
                    GLUL::Log::LibraryStream().logError("Unsupported image extension: '" + extension + "'");
                    throw GLUL::Exception::InitializationFailed("Unsupported image extension: '" + extension + "'");
                }

                break;
        }
    }

    void Image::load(const std::string& path, const Interface::ImageFile& fileInterface) throw(Exception::InitializationFailed) {
        reset();

        *this = std::move(fileInterface.read(path));
    }
    
    void Image::load(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data, bool isRGB) {
        unsigned int rowStride;

        reset();

        _width = width;
        _height = height;
        _bits = bits;
        rowStride = getAlignedRowSize(getWidth(), getBits());

        _size = _height * rowStride;

        if(_size > 0 && data != nullptr) {
            _data = new unsigned char[_size];
            std::memcpy(_data, data, _size);
        } else {
            reset();
        }

        if(isRGB == false) {
            try {
                swapComponents(_width, _height, _bits, _data);
            } catch(const GLUL::Exception::InvalidArgument& exception) {
                GLUL::Log::LibraryStream().logWarning(exception.what());
            }
        }
    }
    
    void Image::save(const std::string& path, Format format) throw(Exception::InitializationFailed) {
        switch(format) {
            case Format::BMP: save(path, GLUL::Interface::ImageFileBMP()); break;
            case Format::TGA: save(path, GLUL::Interface::ImageFileTGA()); break;
            case Format::JPG: save(path, GLUL::Interface::ImageFileJPG()); break;
            case Format::PNG: save(path, GLUL::Interface::ImageFilePNG()); break;

            default:
                std::string extension = GLUL::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP") {
                    save(path, GLUL::Interface::ImageFileBMP());
                } else if(extension == "tga" || extension == "TGA") {
                    save(path, GLUL::Interface::ImageFileTGA());
                } else if(extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG") {
                    save(path, GLUL::Interface::ImageFileJPG());
                } else if(extension == "png" || extension == "PNG") {
                    save(path, GLUL::Interface::ImageFilePNG());
                } else {
                    GLUL::Log::LibraryStream().logError("Unsupported image extension: '" + extension + "'");
                    throw GLUL::Exception::InitializationFailed("Unsupported image extension: '" + extension + "'");
                }

                break;
        }
    }

    void Image::save(const std::string& path, const Interface::ImageFile& fileInterface) throw(Exception::InitializationFailed) {
        fileInterface.save(*this, path);
    }

    void Image::reset() throw() {
        if(_data != nullptr)
            delete[] _data;

        _width = 0; 
        _height = 0;
        _bits = 0;
        _size = 0;
        _data = nullptr;
    }

    void Image::crop(const glm::uvec2& origin, const glm::uvec2& size) {
        unsigned int oldRowStride;
        unsigned int newRowStride;
        unsigned int newOffset;
        unsigned int newSize;
        unsigned char* newData;
        unsigned int newRowWidth;
        
        glm::uvec2 boundaryOrigin = origin;
        glm::uvec2 boundarySize = size;

        // Move origin point inside image's boundaries and change input size to match image's size
        if(boundaryOrigin.x >= getWidth())                  boundaryOrigin.x = getWidth() -1;
        if(boundaryOrigin.y >= getHeight())                 boundaryOrigin.y = getHeight() -1;

        if(boundarySize.x + boundaryOrigin.x > getWidth())  boundarySize.x = getWidth()  - boundaryOrigin.x;
        if(boundarySize.y + boundaryOrigin.y > getHeight()) boundarySize.y = getHeight() - boundaryOrigin.y;

        // Compute offsets in memory to peform copying of data
        oldRowStride = getAlignedRowSize(getWidth(), getBits());
        newRowStride = getAlignedRowSize(boundarySize.x, getBits());
        newRowWidth  = boundarySize.x * (getBits() / 8);

        newOffset = 0;
        newSize = boundarySize.y * newRowStride;

        // Copy cropped data into new array
        newData = new unsigned char[newSize];
        for(unsigned int row = boundaryOrigin.y; row < boundaryOrigin.y + boundarySize.y; ++row) {
            std::memcpy(newData + newOffset, _data + row * oldRowStride + boundaryOrigin.x * (getBits() / 8), newRowWidth);
            std::memset(newData + newOffset + newRowWidth, 0, newRowStride - newRowWidth); // reset aligned bytes to zero
            newOffset += newRowStride;
        }

        // Delete old data
        delete[] _data;

        // Assing new values
        _width = boundarySize.x;
        _height = boundarySize.y;
        _size = newSize;
        _data = newData;
    }

    void Image::rotate90CW() {
        Image old = std::move(*this);
        unsigned int oldRowStride = getAlignedRowSize(old.getWidth(),  old.getBits());
        unsigned int newRowStride = getAlignedRowSize(old.getHeight(), old.getBits());
        unsigned int newRowWidth = old.getHeight() * (old.getBits() / 8);
        unsigned int newRow = 0;
        unsigned int newPixel = 0;
        unsigned int bytes = old.getBits() / 8;
        unsigned char* oldPtr;
        unsigned char* newPtr;
        unsigned char buffer[4];

        // Set rotate'd parameters
        _width = old.getHeight();
        _height = old.getWidth();
        _bits = old.getBits();
        _size = _height * newRowStride;
        _data = new unsigned char[_size];

        //Copy data with rotation
        for(unsigned int oldRow = 0; oldRow < old.getHeight(); ++oldRow) {
            newPixel = oldRow;

            for(unsigned int oldPixel = 0; oldPixel < old.getWidth(); ++oldPixel) {
                newRow = old.getWidth() - oldPixel - 1;

                oldPtr = old._data + oldRow * oldRowStride + oldPixel * bytes;
                newPtr = _data + newRow * newRowStride + newPixel * bytes;

                std::memcpy(buffer, oldPtr, bytes);
                std::memcpy(oldPtr, newPtr, bytes);
                std::memcpy(newPtr, buffer, bytes);
            }
        }
        
        // Clearing aligned bytes
        if((_bits / 8) % 4 != 0) {
            for(unsigned int newRow = 0; newRow < _height; ++newRow) {
                std::memset(_data + newRow * newRowStride + newRowWidth, 0, newRowStride - newRowWidth);
            }
        }
    }

    void Image::rotate90CCW() {
        Image old = std::move(*this);
        unsigned int oldRowStride = getAlignedRowSize(old.getWidth(),  old.getBits());
        unsigned int newRowStride = getAlignedRowSize(old.getHeight(), old.getBits());
        unsigned int newRowWidth = old.getHeight() * (old.getBits() / 8);
        unsigned int newRow = 0;
        unsigned int newPixel = 0;
        unsigned int bytes = old.getBits() / 8;
        unsigned char* oldPtr;
        unsigned char* newPtr;
        unsigned char buffer[4];

        // Set rotate'd parameters
        _width = old.getHeight();
        _height = old.getWidth();
        _bits = old.getBits();
        _size = _height * newRowStride;
        _data = new unsigned char[_size];

        //Copy data with rotation
        for(unsigned int oldRow = 0; oldRow < old.getHeight(); ++oldRow) {
            newPixel = old.getHeight() - oldRow - 1;

            for(unsigned int oldPixel = 0; oldPixel < old.getWidth(); ++oldPixel) {
                newRow = oldPixel;

                oldPtr = old._data + oldRow * oldRowStride + oldPixel * bytes;
                newPtr = _data + newRow * newRowStride + newPixel * bytes;

                std::memcpy(buffer, oldPtr, bytes);
                std::memcpy(oldPtr, newPtr, bytes);
                std::memcpy(newPtr, buffer, bytes);
            }
        }
        
        // Clearing aligned bytes
        if((_bits / 8) % 4 != 0) {
            for(unsigned int newRow = 0; newRow < _height; ++newRow) {
                std::memset(_data + newRow * newRowStride + newRowWidth, 0, newRowStride - newRowWidth);
            }
        }
    }

    void Image::rotate180() {
        unsigned int rowStride = getAlignedRowSize(getWidth(), getBits());
        unsigned int rowWidth = getWidth() * (getBits() / 8);
        unsigned char buffer[4];
        unsigned int bytes = getBits() / 8;
        unsigned char* pixelPtr[2];

        for(unsigned int row = 0; row < getHeight() / 2; row++) {
            for(unsigned int pixel = 0; pixel < getWidth(); pixel++) {
                pixelPtr[0] = _data + (row * rowStride) + pixel * bytes;
                pixelPtr[1] = _data + (getHeight() - 1 - row) * rowStride + (getWidth() - 1 - pixel) * bytes;

                std::memcpy(buffer, pixelPtr[0], bytes);
                std::memcpy(pixelPtr[0], pixelPtr[1], bytes);
                std::memcpy(pixelPtr[1], buffer, bytes);
            }
        }

        // Flip center row if height is not even
        if(getHeight() % 2 == 1) {
            unsigned int row = getHeight() / 2;

            for(unsigned int pixel = 0; pixel < getWidth() / 2; pixel++) {
                pixelPtr[0] = _data + (row * rowStride) + pixel * bytes;
                pixelPtr[1] = _data + (getHeight() - 1 - row) * rowStride + (getWidth() - 1 - pixel) * bytes;

                std::memcpy(buffer, pixelPtr[0], bytes);
                std::memcpy(pixelPtr[0], pixelPtr[1], bytes);
                std::memcpy(pixelPtr[1], buffer, bytes);
            }
        }
        
        // Clearing aligned bytes
        if((_bits / 8) % 4 != 0) {
            for(unsigned int newRow = 0; newRow < _height; ++newRow) {
                std::memset(_data + newRow * rowStride + rowWidth, 0, rowStride - rowWidth);
            }
        }
    }

    void Image::invertHorizontal() {
        unsigned int rowStride = getAlignedRowSize(getWidth(), getBits());
        unsigned char buffer[4];
        unsigned int bytes = getBits() / 8;
        unsigned char* leftPixelOffset;
        unsigned char* rightPixelOffset;

        for(unsigned int rowOffset = 0; rowOffset < getSize(); rowOffset += rowStride) {
            for(unsigned int pixel = 0; pixel < (getWidth()) / 2; pixel++) {
                leftPixelOffset  = _data + rowOffset + pixel * bytes;
                rightPixelOffset = _data + rowOffset + (getWidth() - 1 - pixel) * bytes;

                std::memcpy(buffer, leftPixelOffset, bytes);
                std::memcpy(leftPixelOffset, rightPixelOffset, bytes);
                std::memcpy(rightPixelOffset, buffer, bytes);
            }
        }
    }

    void Image::invertVertical() {
        unsigned int rowStride = getAlignedRowSize(getWidth(), getBits());
        unsigned char buffer[4];
        unsigned int bytes = getBits() / 8;
        unsigned char* topPixelOffset;
        unsigned char* bottomPixelOffset;

        for(unsigned int row = 0; row < (getHeight()) / 2; row++) {
            for(unsigned int pixelOffset = 0; pixelOffset < rowStride - bytes; pixelOffset += bytes) {
                bottomPixelOffset  = _data + pixelOffset + (row * rowStride);
                topPixelOffset     = _data + pixelOffset + (getHeight() - 1 - row) * rowStride; 

                std::memcpy(buffer, bottomPixelOffset, bytes);
                std::memcpy(bottomPixelOffset, topPixelOffset, bytes);
                std::memcpy(topPixelOffset, buffer, bytes);
            }
        }
    }

    void Image::invertColors() {
        unsigned int rowStride;
        unsigned int interval;

        interval = getBits() / 8;
        rowStride = getAlignedRowSize(getWidth(), getBits());
        
        // Invertion of value is done using bitwise negation, becouse when you are using
        // unsigned variables, bitwise negation is equal: ~x = (MAX_VALUE - x)
        auto invertValue = [](unsigned char* dataArray, unsigned int offset) {
            dataArray[offset] = ~(dataArray[offset]);
        };

        for(unsigned int rowOffset = 0; rowOffset < getSize(); rowOffset += rowStride) {
            for(unsigned int pixelOffset = 0; pixelOffset < getWidth() * interval; pixelOffset += interval) {
                if(interval > 0)    invertValue(_data, rowOffset + pixelOffset + 0);
                if(interval > 1)    invertValue(_data, rowOffset + pixelOffset + 1);
                if(interval > 2)    invertValue(_data, rowOffset + pixelOffset + 2);
            }
        }
    }

    void Image::toGrayscale(float percentage) {
        static const glm::vec3 factors = glm::vec3(0.2126f, 0.7152f, 0.0722f);
        unsigned int rowStride;
        unsigned int interval;

        interval = getBits() / 8;
        rowStride = getAlignedRowSize(getWidth(), getBits());

        if(percentage < 0.0f)       percentage = 0.0f;
        else if(percentage > 1.0f)  percentage = 1.0f;

        auto transformPixel = [percentage](unsigned char* dataArray, unsigned int offset) {
            unsigned int newColor = 0;

            newColor += static_cast<unsigned int>(dataArray[offset + 0] * factors.r);
            newColor += static_cast<unsigned int>(dataArray[offset + 1] * factors.g);
            newColor += static_cast<unsigned int>(dataArray[offset + 2] * factors.b);

            dataArray[offset + 0] = static_cast<unsigned char>(percentage * newColor + (1.0f - percentage) * dataArray[offset + 0]);
            dataArray[offset + 1] = static_cast<unsigned char>(percentage * newColor + (1.0f - percentage) * dataArray[offset + 1]);
            dataArray[offset + 2] = static_cast<unsigned char>(percentage * newColor + (1.0f - percentage) * dataArray[offset + 2]);
        };

        if(interval == 3 || interval == 4) {
            for(unsigned int rowOffset = 0; rowOffset < getSize(); rowOffset += rowStride) {
                for(unsigned int pixelOffset = 0; pixelOffset < getWidth() * interval; pixelOffset += interval) {
                    transformPixel(getData(), rowOffset + pixelOffset);
                }
            }
        } else {
            GLUL::Log::LibraryStream().logWarning("Could not convert image to weighted grayscale - not enough channels (" + std::to_string(interval) + ")");
        }
    }

    unsigned int Image::getBits() const {
        return _bits;
    }

    unsigned int Image::getSize() const {
        return _size;
    }

    unsigned int Image::getWidth() const {
        return _width;
    }

    unsigned int Image::getHeight() const {
        return _height;
    }

    unsigned char* Image::getData() const {
        return _data;
    }
    
    glm::uvec4 Image::getPixel(unsigned int x, unsigned int y) const {
        glm::uvec4 result(0, 0, 0, UCHAR_MAX);
        unsigned int mult;
        unsigned int rowStride;
        unsigned int pixelOffset;
        
        mult = getBits() / 8;
        rowStride = getAlignedRowSize(getWidth(), getBits());
        pixelOffset = y * rowStride + x * mult;

        if(_data != nullptr && x < _width && y < _height) {
            if(mult > 0)    result.r = _data[pixelOffset + 0];
            if(mult > 1)    result.g = _data[pixelOffset + 1];
            if(mult > 2)    result.b = _data[pixelOffset + 2];
            if(mult > 3)    result.a = _data[pixelOffset + 3];
        }

        return result;
    }

    void Image::setPixel(unsigned int x, unsigned int y, const glm::uvec4& color) {
        unsigned int mult;
        unsigned int rowStride;
        unsigned int pixelOffset;
        
        mult = getBits() / 8;
        rowStride = getAlignedRowSize(getWidth(), getBits());
        pixelOffset = y * rowStride + x * mult;

        if(_data != nullptr && x < _width && y < _height) {
            if(mult > 0)    _data[pixelOffset + 0] = static_cast<unsigned char>(color.r);
            if(mult > 1)    _data[pixelOffset + 1] = static_cast<unsigned char>(color.g);
            if(mult > 2)    _data[pixelOffset + 2] = static_cast<unsigned char>(color.b);
            if(mult > 3)    _data[pixelOffset + 3] = static_cast<unsigned char>(color.a);
        }
    }
    
    void Image::swapComponents(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) throw(GLUL::Exception::InvalidArgument) {
        unsigned int interval;
        unsigned int rowStride;
        unsigned long long int arraySize;

        switch(bits) {
            case 24: interval = 3; break;
            case 32: interval = 4; break; 

            default:
                throw GLUL::Exception::InvalidArgument("Invalid argument: cannot convert image to RGB(A) format with " + std::to_string(bits/8) + "components");
        }
        
        rowStride = getAlignedRowSize(width, bits);
        arraySize = height * rowStride;

        for(unsigned long long int rowPtr = 0; rowPtr < arraySize; rowPtr += rowStride) {
            for(unsigned int collumnPtr = 0; collumnPtr < width * (bits / 8); collumnPtr += interval) {
                std::swap(data[rowPtr + collumnPtr + 0], data[rowPtr + collumnPtr + 2]);
            }
        }

    }

    unsigned int Image::getAlignedRowSize(unsigned int width, unsigned int bits) {
        unsigned int result;
        
        result = width * (bits / 8);
        result = result + (3 - ((result - 1) % 4));

        return result;
    }

}
