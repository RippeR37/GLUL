#include <Utils/Image.h>
#include <Utils/File.h>
#include <Utils/Logger.h>

#include <jpeglib.h>
#include <png.h>

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

    void Image::load(const std::string& path, Format format) throw(Exception::InitializationFailed) {
        reset();

        switch(format) {
            case Format::BMP: loadBMP(path); break;
            case Format::TGA: loadTGA(path); break;
            case Format::JPG: loadJPG(path); break;
            case Format::PNG: loadPNG(path); break;

            default:
                std::string extension = Util::File::getExtension(path);

                if(extension == "bmp" || extension == "BMP") {
                    loadBMP(path);
                } else if(extension == "tga" || extension == "TGA") {
                    loadTGA(path);
                } else if(extension == "jpg" || extension == "JPG" || extension == "jpeg" || extension == "JPEG") {
                    loadJPG(path);
                } else if(extension == "png" || extension == "PNG") {
                    loadPNG(path);
                } else {
                    Util::Log::LibraryStream().logError("Unsupported image extension: '" + extension + "'");
                    throw Util::Exception::InitializationFailed("Unsupported image extension: '" + extension + "'");
                }

                break;
        }
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

    void Image::loadBMP(const std::string& path) throw(Exception::InitializationFailed) {
        std::string error;
        unsigned char header[54];
        unsigned int dataOffset;

        FILE *file = fopen(path.c_str(), "rb");
        if(!file) {
            reset();
            Util::Log::LibraryStream().logError("Failed to load image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load image file: '" + path + "'");
        }

        if(fread(header, 1, 54, file) != 54) {
            reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Failed to read header of BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read header of BMP image file: '" + path + "'");
        }


        if(header[0] != 'B' || header[1] != 'M') {
            reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Input file is not a correct BMP image file: '" + path + "'");
        }

        if(header[0x1E] || header[0x1F] || header[0x20] || header[0x21]) {
            reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Input file is not a correct BMP image file: '" + path + "'");
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

        if(fread(_data, 1, _size, file) != _size) {
            reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Failed to read whole BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read whole BMP image file: '" + path + "'");
        }

        fclose(file);

        try {
            swapComponents(_width, _height, _bits, _data);
        } catch(const Util::Exception::InvalidArgument& exception) {
            Util::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
        }
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
            reset();
            Util::Log::LibraryStream().logError("Failed to load TGA image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load TGA image file: '" + path + "'");
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
            reset();
            Util::Log::LibraryStream().logError("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
        }

        if(c_mode != 3 && c_mode != 4) {
            reset();
            Util::Log::LibraryStream().logError("Unsupported TGA color bits: '" + std::to_string(c_mode) + "' in file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported TGA color bits: '" + std::to_string(c_mode) + "' in file: '" + path + "'");
        }

        if(id_len > 0)
            fileStream.read(buff, id_len);
        if(cm_type != 0 && cm_len > 0)
            fileStream.read(buff, cm_len);

        _data = new unsigned char[_size];
        fileStream.read((char*)_data, _size);
        fileStream.close();

        try {
            swapComponents(_width, _height, _bits, _data);
        } catch(const Util::Exception::InvalidArgument& exception) {
            Util::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
        }
    }

    void Image::loadJPG(const std::string& path) {
        jpeg_decompress_struct cinfo;
        jpeg_error_mgr jerr;
        int rowStride;
        unsigned char** dataRow;

        // Opening file with JPEG image
        FILE* file;
        if((file = fopen(path.c_str(), "rb")) == nullptr) {
            reset();
            Util::Log::LibraryStream().logError("Failed to load JPEG image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load JPEG image file: '" + path + "'");
        }

        cinfo.err = jpeg_std_error(&jerr);
        
        // Creating decompressing object and pointing it's source
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, file);
        
        // Reading header
        jpeg_read_header(&cinfo, true);

        // 
        // parameteres for decompression here
        // 

        // Decompressing image data
        jpeg_start_decompress(&cinfo);

        // Writing image's header data
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
    }

    void Image::loadPNG(const std::string& path) throw(Exception::InitializationFailed) {
        /*** Variables ***/
        png_byte header[8];
        int bitDepth;
        int colorType;
        int rowBytes;

        /*** Implementation ***/
        FILE *fp = fopen(path.c_str(), "rb");
        if(fp == 0) {
            reset();
            Util::Log::LibraryStream().logError("Failed to load PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load PNG image file: '" + path + "'");
        }

        fread(header, 1, 8, fp);
        if(png_sig_cmp(header, 0, 8)) {
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Loaded file is not a proper PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Loaded file is not a proper PNG image file: '" + path + "'");
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr) {
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            png_destroy_read_struct(&png_ptr, nullptr, nullptr);
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info) {
            png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        
        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file (SJ): '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file (SJ): '" + path + "'");
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        png_get_IHDR(png_ptr, info_ptr, &_width, &_height, &bitDepth, &colorType, nullptr, nullptr, nullptr);

        if (bitDepth != 8) {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            reset();
            Util::Log::LibraryStream().logError("Unsupported bit depth in PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
        }

        switch(colorType) {
            case PNG_COLOR_TYPE_RGB:        _bits = 24; break;
            case PNG_COLOR_TYPE_RGB_ALPHA:  _bits = 32; break;

            default:
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                reset();
                Util::Log::LibraryStream().logError("Unsupported color type '" + std::to_string(colorType) + "' in PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
        }

        png_read_update_info(png_ptr, info_ptr);
        rowBytes  = png_get_rowbytes(png_ptr, info_ptr);

        _data = new unsigned char[rowBytes * _height];
        unsigned char** rowPointers = new unsigned char*[_height];

        for(unsigned int i = 0; i < _height; i++)
            rowPointers[_height -1 - i] = _data + i * rowBytes;

        png_read_image(png_ptr, rowPointers);

        /// Cleaning up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        delete[] rowPointers;
    }

}
