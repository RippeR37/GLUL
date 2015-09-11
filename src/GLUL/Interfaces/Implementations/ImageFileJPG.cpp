#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFileJPG.h>

#include <jpeglib.h>

#include <cstring>


namespace GLUL {

    namespace Interface {

        Image ImageFileJPG::read(const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            Image image;
            unsigned int width, height, bits;
            unsigned char* data;

            jpeg_decompress_struct cinfo;
            jpeg_error_mgr jerr;
            int rowStride;
            unsigned char** dataRow;

            // Opening file with JPEG image
            FILE* file;
            if((file = fopen(path.c_str(), "rb")) == nullptr) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to load JPEG image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to load JPEG image file: '" + path + "'");
            }

            cinfo.err = jpeg_std_error(&jerr);
        
            // Creating decompressing object and pointing it's source
            jpeg_create_decompress(&cinfo);
            jpeg_stdio_src(&cinfo, file);
        
            // Reading header
            jpeg_read_header(&cinfo, TRUE);

            // 
            // parameteres for decompression here
            // 

            // Decompressing image data
            jpeg_start_decompress(&cinfo);

            // Writing image's header data
            width = cinfo.output_width;
            height = cinfo.output_height;
            bits = cinfo.output_components * 8;

            rowStride = Image::getAlignedRowSize(width, bits);

            data = new unsigned char[height * rowStride];
            dataRow = new unsigned char*[1];
            dataRow[0] = new unsigned char[rowStride];

            // Reading data
            unsigned int offset = (height - 1) * rowStride; // width * (bits / 8);
            while(cinfo.output_scanline < cinfo.output_height) {
                // Read row
                jpeg_read_scanlines(&cinfo, dataRow, 1);

                // Copy result image data to _data array in reverse order
                std::memcpy(data + offset, dataRow[0], rowStride);
                offset -= rowStride;
            }
            jpeg_finish_decompress(&cinfo);

            /// Cleaning up
            jpeg_destroy_decompress(&cinfo);
            fclose(file);

            delete[] dataRow[0];
            delete[] dataRow;

            // set image's member variables
            setImage(image, width, height, bits, data);

            return image;
        }

        void ImageFileJPG::save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            (void) image;
            (void) path;

            throw GLUL::Exception("ImageFileJPG::save(...) not yet implemented");
        }

    }

}
