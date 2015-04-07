#include <Utils/Image.h>
#include <Utils/File.h>
#include <Utils/Logger.h>

#include <jpeglib.h>

#include <algorithm>
#include <cstdio>
#include <climits>
#include <fstream>
#include <iterator>

#include <iostream>

namespace Util {

    Image::Image(const std::string& path, Format format) {
        _data = nullptr;

        switch(format) {
            case Format::BMP:
                loadBMP(path);
                break;

            case Format::TGA:
                loadTGA(path);
                break;

            case Format::JPG:
                loadJPG(path);
                break;

            default:
                std::string extension = Util::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP")
                    loadBMP(path);
                else if(extension == "tga" || extension == "TGA")
                    loadTGA(path);
                else if(extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG")
                    loadJPG(path);
                else
                    Util::Log::LibraryStream().logError("Unknown image extension: '" + extension + "'");

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
            Util::Log::LibraryStream().logError("Failed to load image file: '" + path + "'");
            return;
        }

        if(fread(header, 1, 54, file) != 54) {
            Util::Log::LibraryStream().logError("Failed to read header of BMP image file: '" + path + "'");
            fclose(file);
            return;
        }


        if(header[0] != 'B' || header[1] != 'M') {
            Util::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
            fclose(file);
            return;
        }

        if(header[0x1E] || header[0x1F] || header[0x20] || header[0x21]) {
            Util::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
            fclose(file);
            return;
        }

        // BMP files have integer data saved with Little Endian convention
        auto getUIntFromUCharArrayLE = [](unsigned char* ptr) -> int {
            unsigned int result = 0;

            for(unsigned int i = 0; i < 4; ++i)
                result |= (*(ptr + i) << i * CHAR_BIT);

            return result;
        };

        dataOffset  = getUIntFromUCharArrayLE(&header[0x0A]);
        _size       = getUIntFromUCharArrayLE(&header[0x22]);
        _width      = getUIntFromUCharArrayLE(&header[0x12]);
        _height     = getUIntFromUCharArrayLE(&header[0x16]);
        _bits       = getUIntFromUCharArrayLE(&header[0x1C]);

        if(_size == 0)
            _size = _width * _height * (_bits / 8);

        if(dataOffset == 0)
            dataOffset = 54;

        _data = new unsigned char[_size];

        if(fread(_data, 1, _size, file) != _size)
            Util::Log::LibraryStream().logError("Failed to read whole BMP image file: '" + path + "'");

        fclose(file);
    }

    void Image::loadTGA(const std::string& path) {
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
            Util::Log::LibraryStream().logError("Failed to load TGA image file: '" + path + "'");
            return;
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
            Util::Log::LibraryStream().logError("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
            return;
        }

        if(c_mode != 3 && c_mode != 4) {
            Util::Log::LibraryStream().logError("Unsupported TGA color bits: '" + std::to_string(c_mode) + "' in file: '" + path + "'");
            return;
        }

        if(id_len > 0)
            fileStream.read(buff, id_len);
        if(cm_type != 0 && cm_len > 0)
            fileStream.read(buff, cm_len);

        _data = new unsigned char[_size];
        fileStream.read((char*)_data, _size);
        fileStream.close();
    }

    void Image::loadJPG(const std::string& path) {
        jpeg_decompress_struct cinfo;
        jpeg_error_mgr jerr;
        int rowStride;
        unsigned char** dataRow;

        FILE* file;
        if((file = fopen(path.c_str(), "rb")) == nullptr) {
            std::cerr << "Could not open file '" << path << "'" << std::endl;
            return;
        }

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, file);
        
        jpeg_read_header(&cinfo, true);

        // parameteres for decompression here

        jpeg_start_decompress(&cinfo);

        _width = cinfo.output_width;
        _height = cinfo.output_height;
        _bits = cinfo.output_components * 8;
        _data = new unsigned char[_width * _height * _bits / 8];

        rowStride = cinfo.output_width * cinfo.output_components;
        dataRow = new unsigned char*[1];
        dataRow[0] = new unsigned char[rowStride];

        // Reading data
        unsigned int offset = (_height - 1) * _width * _bits / 8;
        while(cinfo.output_scanline < cinfo.output_height) {
            // Read row
            jpeg_read_scanlines(&cinfo, dataRow, 1);

            // Transform RGB -> BGR
            for(int i = 0; i < rowStride; i += cinfo.output_components)
                std::swap(dataRow[0][i], dataRow[0][i+2]);

            // Copy result image data to _data array in reverse order
            std::memcpy(_data + offset, dataRow[0], rowStride);
            offset -= rowStride;
        }

        jpeg_finish_decompress(&cinfo);

        /// Cleaning up
        jpeg_destroy_decompress(&cinfo);
        fclose(file);

        delete[] dataRow[0];
        delete[] dataRow;

        return;
    }

}
