#include <Utils/Image.h>
#include <Utils/File.h>
#include <Utils/Logger.h>

#include <Utils/Interfaces/Implementations/ImageFileBMP.h>
#include <Utils/Interfaces/Implementations/ImageFileTGA.h>
#include <Utils/Interfaces/Implementations/ImageFileJPG.h>
#include <Utils/Interfaces/Implementations/ImageFilePNG.h>

#include <algorithm>
#include <cstdio>
#include <climits>
#include <fstream>
#include <iterator>

#include <iostream>

namespace Util {

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
        reset();

        switch(format) {
            case Format::BMP: load(path, Util::ImageFileBMP()); break;
            case Format::TGA: load(path, Util::ImageFileTGA()); break;
            case Format::JPG: load(path, Util::ImageFileJPG()); break;
            case Format::PNG: load(path, Util::ImageFilePNG()); break;

            default:
                std::string extension = Util::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP") {
                    load(path, Util::ImageFileBMP());
                } else if(extension == "tga" || extension == "TGA") {
                    load(path, Util::ImageFileTGA());
                } else if(extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG") {
                    load(path, Util::ImageFileJPG());
                } else if(extension == "png" || extension == "PNG") {
                    load(path, Util::ImageFilePNG());
                } else {
                    Util::Log::LibraryStream().logError("Unsupported image extension: '" + extension + "'");
                    throw Util::Exception::InitializationFailed("Unsupported image extension: '" + extension + "'");
                }

                break;
        }
    }

    void Image::load(const std::string& path, const Interface::ImageFile& fileInterface) {
        *this = std::move(fileInterface.read(path));
    }
    
    void Image::load(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data, bool isRGB) {
        _width = width;
        _height = _height;
        _bits = bits;
        _size = _width * _height * _bits / 8;

        if(_size > 0 && data != nullptr) {
            _data = new unsigned char[_size];
            std::memcpy(_data, data, _size);
        } else {
            reset();
        }

        if(isRGB == false) {
            try {
                swapComponents(_width, _height, _bits, _data);
            } catch(const Util::Exception::InvalidArgument& exception) {
                Util::Log::LibraryStream().logWarning(exception.what());
            }
        }
    }

    void Image::reset() {
        if(_data != nullptr)
            delete[] _data;

        _width = 0; 
        _height = 0;
        _bits = 0;
        _size = 0;
        _data = nullptr;
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
        glm::uvec4 result(0, 0, 0, INT_MAX);

        if(_data != nullptr && x < _width && y < _height) {
            switch(getBits()) {
                case 8:
                    result.r = _data[(y * _width + x) * 1 + 0];
                    break;

                case 16: 
                    result.r = _data[(y * _width + x) * 2 + 0];
                    result.g = _data[(y * _width + x) * 2 + 1];
                    break;

                case 24: 
                    result.r = _data[(y * _width + x) * 3 + 0];
                    result.g = _data[(y * _width + x) * 3 + 1];
                    result.b = _data[(y * _width + x) * 3 + 2];
                    break;

                case 32: 
                    result.r = _data[(y * _width + x) * 4 + 0];
                    result.g = _data[(y * _width + x) * 4 + 1];
                    result.b = _data[(y * _width + x) * 4 + 2];
                    result.a = _data[(y * _width + x) * 4 + 3];
                    break;
            }
        }

        return result;
    }
    
    void Image::swapComponents(unsigned int width, unsigned int height, unsigned int bits, unsigned char* data) throw(Util::Exception::InvalidArgument) {
        unsigned long long int arraySize = width * height * (bits / 8);
        unsigned int interval = 3;

        switch(bits) {
            case 24: interval = 3; break;
            case 32: interval = 4; break; 

            default:
                throw Util::Exception::InvalidArgument("Invalid argument: cannot convert image to RGB(A) format with " + std::to_string(bits/8) + "components");
        }

        for(unsigned long long int i = 0; i < arraySize; i += interval)
            std::swap(data[i], data[i+2]);
    }

}
