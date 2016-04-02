#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFilePNG.h>

#include <png.h>


namespace GLUL {

    namespace Interface {

        Image ImageFilePNG::read(const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            Image image;
            png_uint_32 width, height;
            unsigned int bits;
            unsigned char* data;

            png_byte header[8];
            int bitDepth;
            int colorType;
            int rowStride;


            FILE *fp = fopen(path.c_str(), "rb");
            if(fp == nullptr) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to load PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to load PNG image file: '" + path + "'");
            }

            if(fread(header, 1, 8, fp) != 8) {
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Loaded file is not a proper PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Loaded file is not a proper PNG image file: '" + path + "'");
            }

            if(png_sig_cmp(header, 0, 8)) {
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Loaded file is not a proper PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Loaded file is not a proper PNG image file: '" + path + "'");
            }

            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if (!png_ptr) {
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
            }

            png_infop info_ptr = png_create_info_struct(png_ptr);
            if (!info_ptr) {
                png_destroy_read_struct(&png_ptr, nullptr, nullptr);
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
            }

            png_infop end_info = png_create_info_struct(png_ptr);
            if (!end_info) {
                png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to read PNG image from file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to read PNG image from file: '" + path + "'");
            }

        
            if (setjmp(png_jmpbuf(png_ptr))) {
                png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                fclose(fp);
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to read PNG image from file (SJ): '" + path + "'");
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
                GLUL::Log::LibraryStream().logError("Unsupported bit depth in PNG image file: '" + path + "'");
                throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
            }

            switch(colorType) {
                case PNG_COLOR_TYPE_RGB:        bits = 24; break;
                case PNG_COLOR_TYPE_RGB_ALPHA:  bits = 32; break;

                default:
                    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
                    fclose(fp);
                    image.reset();
                    GLUL::Log::LibraryStream().logError("Unsupported color type '" + std::to_string(colorType) + "' in PNG image file: '" + path + "'");
                    throw Exception::InitializationFailed("Unsupported bit depth in PNG image file: '" + path + "'");
            }

            png_read_update_info(png_ptr, info_ptr);

            rowStride = Image::getAlignedRowSize(width, bits);

            data = new unsigned char[height * rowStride];
            unsigned char** rowPointers = new unsigned char*[height];

            for(unsigned int row = 0; row < height; ++row)
                rowPointers[height -1 - row] = data + row * rowStride;

            png_read_image(png_ptr, rowPointers);

            // Cleaning up
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            delete[] rowPointers;

            // Set image's member variables
            setImage(image, static_cast<unsigned int>(width), static_cast<unsigned int>(height), bits, data);

            return image;
        }

        void ImageFilePNG::save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            png_structp png_ptr;
            png_infop info_ptr;
            png_byte colorType;
            png_uint_32 width = image.getWidth();
            png_uint_32 height = image.getHeight();
            png_byte bitDepth = 8;
            unsigned int bits = image.getBits();
            unsigned char* data = image.getData();
            int rowStride = Image::getAlignedRowSize(image.getWidth(), bits);
            unsigned char** rowPointers;

            switch(bits) {
                case 24: colorType = PNG_COLOR_TYPE_RGB; break;
                case 32: colorType = PNG_COLOR_TYPE_RGBA; break;

                default:
                    GLUL::Log::LibraryStream().logError(
                        "Failed to save PNG image file: '" + path + "'."
                        "Unsupported BPP value: " + std::to_string(bits) + "!");
                    return;
            }

            FILE *fp = fopen(path.c_str(), "wb");
            if(fp == nullptr)
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't open file!");


            png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

            if(!png_ptr) {
                fclose(fp);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't create png write structure!");
                return;
            }

            info_ptr = png_create_info_struct(png_ptr);
            if(!info_ptr) {
                fclose(fp);
                png_destroy_write_struct(&png_ptr, nullptr);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't create png info structure!");
                return;
            }

            if(setjmp(png_jmpbuf(png_ptr))) {
                fclose(fp);
                png_destroy_write_struct(&png_ptr, &info_ptr);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. IO initialization failed!");
                return;
            }
            png_init_io(png_ptr, fp);


            if(setjmp(png_jmpbuf(png_ptr))) {
                fclose(fp);
                png_destroy_write_struct(&png_ptr, &info_ptr);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't write headers!");
                return;
            }
            png_set_IHDR(png_ptr, info_ptr, width, height, bitDepth, colorType, 
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
            png_write_info(png_ptr, info_ptr);


            // Prepare row pointers
            rowPointers = new unsigned char*[height];
            for(unsigned int row = 0; row < height; ++row)
                rowPointers[height - 1 - row] = data + row * rowStride;


            // Write image data
            if(setjmp(png_jmpbuf(png_ptr))) {
                fclose(fp);
                png_destroy_write_struct(&png_ptr, &info_ptr);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't write image data!");
                return;
            }
            png_write_image(png_ptr, rowPointers);


            if(setjmp(png_jmpbuf(png_ptr))) {
                fclose(fp);
                png_destroy_write_struct(&png_ptr, &info_ptr);
                GLUL::Log::LibraryStream().logError("Failed to save PNG image file: '" + path + "'. Can't write end of image!");
                return;
            }
            png_write_end(png_ptr, nullptr);


            // Cleaning up
            png_destroy_write_struct(&png_ptr, &info_ptr);
            fclose(fp);
            delete[] rowPointers;
        }

    }

}
