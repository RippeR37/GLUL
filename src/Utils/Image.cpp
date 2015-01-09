#include <Utils/Image.h>

#include <cstdio>

namespace Util {

    Image::Image(std::string path, Image::Format format) {
        switch(format) {
            case Format::BMP: 
                loadBMP(path);
                break;
                
            default:
                break;
        }
    }

    Image::~Image() {
        delete[] _data;
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

    void Image::loadBMP(const std::string& path) {
        std::string error;
        unsigned char header[54];
        unsigned int dataOffset;

        FILE *file = fopen(path.c_str(), "rb");
        if(!file) {
            
        }

        if(fread(header, 1, 54, file) != 54) {
            error = "Failed to read header of BMP image file: '" + path + "'";
            throw Exception::FatalError(error.c_str());
        }
        

        if(header[0] != 'B' || header[1] != 'M') {
            error = "Input file is not a correct BMP image file: '" + path + "'";
            throw Exception::FatalError(error.c_str());
        }

        if(*(unsigned int*)&(header[0x1E]) != 0) {
            error = "Input file is not a correct BMP image file: '" + path + "'";
            throw Exception::FatalError(error.c_str());
        }

        dataOffset  = *(unsigned int*)&(header[0x0A]);
        _size       = *(unsigned int*)&(header[0x22]);
        _width      = *(unsigned int*)&(header[0x12]);
        _height     = *(unsigned int*)&(header[0x16]);
        _bits       = *(unsigned int*)&(header[0x1C]);

        if(_size == 0)
            _size = _width * _height * (_bits / 8);

        if(dataOffset == 0) 
            dataOffset = 54;

        _data = new unsigned char[_size];
        
        if(fread(_data, 1, _size, file) != _size) {
            error = "Could not read whole BMP image file: '" + path + "'";
            throw Exception::FatalError(error.c_str());
        }

        fclose(file);
    }

}