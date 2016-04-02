#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFileJPG.h>

#include <jpeglib.h>

#include <cstring>
#include <vector>


namespace GLUL {

    namespace Interface {

        // Default quality value, can be changed by user
        int ImageFileJPG::defaultQuality = 95;

        // Default constructor - uses ImageFileJPG::defaultQuality as quality value
        ImageFileJPG::ImageFileJPG() : ImageFileJPG(ImageFileJPG::defaultQuality) { }

        // Custom constructor - set's quality to argument value
        ImageFileJPG::ImageFileJPG(int quality) : _quality(quality) { }


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
            jpeg_compress_struct cinfo;
            jpeg_error_mgr jerr;
            JSAMPROW rowPointer[1];
            FILE* fp;
            int components = 3;
            int rowStride = Image::getAlignedRowSize(image.getWidth(), components * 8); // always save in RGB format
            J_COLOR_SPACE colorSpace = J_COLOR_SPACE::JCS_RGB;
            unsigned char* data = nullptr;
            std::vector<unsigned char> rgbData; // used when stripping or suplementing image format to RGB
                                                // e.g. RGBA->RGB or R->RGB

            switch(image.getBits()) {
                case 24: data = image.getData(); break;

                default:
                    rgbData = std::move(getRGBDataOf(image));
                    data = rgbData.data();
            }

            cinfo.err = jpeg_std_error(&jerr);
            jpeg_create_compress(&cinfo);

            fp = fopen(path.c_str(), "wb");
            if(!fp) {
                GLUL::Log::LibraryStream().logError("Failed to save JPEG image file: '" + path + "'. Can't open file!");
                return;
            }
            jpeg_stdio_dest(&cinfo, fp);

            cinfo.image_width = image.getWidth();
            cinfo.image_height = image.getHeight();
            cinfo.input_components = components;
            cinfo.in_color_space = colorSpace;

            jpeg_set_defaults(&cinfo);
            jpeg_set_quality(&cinfo, _quality, true);
            jpeg_start_compress(&cinfo, true);

            while(cinfo.next_scanline < cinfo.image_height) {
                rowPointer[0] = data + (cinfo.image_height - cinfo.next_scanline - 1) * rowStride;
                (void) jpeg_write_scanlines(&cinfo, rowPointer, 1);
            }

            jpeg_finish_compress(&cinfo);
            fclose(fp);
            jpeg_destroy_compress(&cinfo);
        }

    }

}
