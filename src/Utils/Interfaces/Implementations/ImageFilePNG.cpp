#include <Utils/Logger.h>
#include <Utils/Interfaces/Implementations/ImageFilePNG.h>

#include <png.h>

namespace Util {

    Image ImageFilePNG::read(const std::string& path) const throw(Util::Exception::InitializationFailed) {
        Image image;
        unsigned int width, height, bits;
        unsigned char* data;

        png_byte header[8];
        int bitDepth;
        int colorType;
        int rowBytes;


        FILE *fp = fopen(path.c_str(), "rb");
        if(fp == 0) {
            image.reset();
            Util::Log::LibraryStream().logError("Failed to load PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load PNG image file: '" + path + "'");
        }

        fread(header, 1, 8, fp);
        if(png_sig_cmp(header, 0, 8)) {
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Loaded file is not a proper PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Loaded file is not a proper PNG image file: '" + path + "'");
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr) {
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            png_destroy_read_struct(&png_ptr, nullptr, nullptr);
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info) {
            png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
        }

        
        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Failed to read PNG image from file (SJ): '" + path + "'");
            throw Exception::InitializationFailed("Failed to read PNG image from file (SJ): '" + path + "'");
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType, nullptr, nullptr, nullptr);

        if (bitDepth != 8) {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            image.reset();
            Util::Log::LibraryStream().logError("Unsupported bit depth in PNG image file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
        }

        switch(colorType) {
            case PNG_COLOR_TYPE_RGB:        bits = 24; break;
            case PNG_COLOR_TYPE_RGB_ALPHA:  bits = 32; break;

            default:
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                image.reset();
                Util::Log::LibraryStream().logError("Unsupported color type '" + std::to_string(colorType) + "' in PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
        }

        png_read_update_info(png_ptr, info_ptr);
        rowBytes  = png_get_rowbytes(png_ptr, info_ptr);

        data = new unsigned char[rowBytes * height];
        unsigned char** rowPointers = new unsigned char*[height];

        for(unsigned int i = 0; i < height; i++)
            rowPointers[height -1 - i] = data + i * rowBytes;

        png_read_image(png_ptr, rowPointers);

        /// Cleaning up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        delete[] rowPointers;

        // set image's member variables
        setImage(image, width, height, bits, data);

        return image;
    }

    void ImageFilePNG::save(const std::string& path) const throw(Util::Exception::InitializationFailed) {
        throw Util::Exception("ImageFilePNG::save(...) not yet implemented");
    }

}