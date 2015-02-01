#include <Utils/Image.h>
#include <utils/File.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iterator>

namespace Util {

    Image::Image(std::string path, Image::Format format) {
        _data = nullptr;

        switch(format) {
            case Format::BMP: 
                loadBMP(path);
                break;

            case Format::TGA:
                loadTGA(path);
                break;

            default:
                std::string extension = Util::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP")
                    loadBMP(path);
                else if(extension == "tga" || extension == "TGA")
                    loadTGA(path);
                else
                    throw Exception::FatalError("Unknown image extension: " + extension);

                break;
        }
    }

    Image::Image(const Image& image) {
        _size   = image._size;
        _width  = image._width;
        _height = image._height;
        _bits   = image._bits;
        _data   = nullptr;

        if(image._data != nullptr)
            _data = new unsigned char[_size];

        std::copy(image._data, image._data + image._size, _data);
    }

    Image::Image(Image&& image) :
        _size(std::move(image._size)),
        _width(std::move(image._width)),
        _height(std::move(image._height)),
        _bits(std::move(image._bits)),
        _data(std::move(image._data))
    {
        image._data = nullptr;
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
            error = "Failed to load image file: " + path;
            throw Exception::FatalError(error.c_str());
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

    void Image::loadTGA(const std::string& path) throw(Exception::FatalError) {
        std::ifstream fileStream;
        std::string error;
        char buff[256];
        char c;
        char si_a[2];
        char* si = (char*)&si_a[0];
        int id_len, cm_type, type;
        int cm_len;
        int c_mode;

        fileStream.open(path, std::fstream::binary);
        if(fileStream.is_open() == false) {
            error = "Failed to load image file: " + path;
            throw Exception::FatalError(error.c_str());
        }

        fileStream.read(&c, 1);         id_len  = (int)c;
        fileStream.read(&c, 1);         cm_type = (int)c;
        fileStream.read(&c, 1);         type    = (int)c;

        fileStream.read(si, 2);         // cm index
        fileStream.read(si, 2);         cm_len  = (si[1] << 8) | si[0];
        fileStream.read(&c, 1);         // cm bpp

        fileStream.read(si, 2);         // x_or
        fileStream.read(si, 2);         // y_or
        fileStream.read(si, 2);         _width  = (si[1] << 8) | si[0];
        fileStream.read(si, 2);         _height = (si[1] << 8) | si[0];
        fileStream.read(&c, 1);         _bits = (int)c;
        fileStream.read(&c, 1);         // img descriptor

        c_mode = _bits / 8;
        _size  = _width * _height * c_mode;

        if(type != 2 && type != 3) {
            error = "Unsupported TGA format (" + std::to_string(type) + " in file: " + path;
            throw Exception::FatalError(error.c_str());
        }

        if(c_mode != 3 && c_mode != 4) {
            error = "Unsupported TGA color bits (" + std::to_string(c_mode) +") in file: " + path;
            throw Exception::FatalError(error.c_str());
        }

        if(id_len > 0)
            fileStream.read(buff, id_len);
        if(cm_type != 0 && cm_len > 0)
            fileStream.read(buff, cm_len);

        _data = new unsigned char[_size];
        fileStream.read((char*)_data, _size);
        fileStream.close();
    }

}