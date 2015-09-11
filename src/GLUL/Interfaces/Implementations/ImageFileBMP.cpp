#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFileBMP.h>

#include <climits>
#include <cstring>


namespace GLUL {

    namespace Interface {

        Image ImageFileBMP::read(const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            Image image;
            unsigned char header[54];
            unsigned int dataOffset;
            unsigned int size;
            unsigned int width, height, bits;
            unsigned char* data = nullptr;
            unsigned int rowStride; // width * bits algined to 4bytes

            FILE *file = fopen(path.c_str(), "rb");
            if(!file) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to load image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to load image file: '" + path + "'");
            }

            if(fread(header, 1, 54, file) != 54) {
                image.reset();
                fclose(file);
                GLUL::Log::LibraryStream().logError("Failed to read header of BMP image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to read header of BMP image file: '" + path + "'");
            }


            if(header[0] != 'B' || header[1] != 'M') {
                image.reset();
                fclose(file);
                GLUL::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
                throw Exception::InitializationFailed("Input file is not a correct BMP image file: '" + path + "'");
            }

            if(header[0x1E] || header[0x1F] || header[0x20] || header[0x21]) {
                image.reset();
                fclose(file);
                GLUL::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
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
            size        = getUIntFromUCharArrayLE(&header[0x22]);
            width       = getUIntFromUCharArrayLE(&header[0x12]);
            height      = getUIntFromUCharArrayLE(&header[0x16]);
            bits        = getUIntFromUCharArrayLE(&header[0x1C]);
            rowStride   = Image::getAlignedRowSize(width, bits);

            if(size == 0)
                size = height * rowStride;

            if(dataOffset != 0 && dataOffset != 54)
                fseek(file, dataOffset, SEEK_SET);

            data = new unsigned char[size];

            if(fread(data, 1, size, file) != size) {
                image.reset();
                fclose(file);
                GLUL::Log::LibraryStream().logError("Failed to read whole BMP image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to read whole BMP image file: '" + path + "'");
            }

            fclose(file);

            try {
                Image::swapComponents(width, height, bits, data);
            } catch(const GLUL::Exception::InvalidArgument& exception) {
                GLUL::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
            }

            // set image's member variables
            setImage(image, width, height, bits, data);

            return image;
        }

        void ImageFileBMP::save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            union {
                unsigned char headerData[56];
                BMPheader header;
            };
            unsigned char* BGRdata;

            header.bmpID[0] = 0; // not used, dummy byte due to struct alignment
            header.bmpID[1] = 0; // not used, dummy byte due to struct alignment
            header.bmpID[2] = 'B';
            header.bmpID[3] = 'M';
            header.fileSize = image.getSize() + 54;
            header.reserved[0] = 0;
            header.reserved[1] = 0;
            header.dataOffset = 54;
            header.headerSize = 40;
            header.width = image.getWidth();
            header.height = image.getHeight();
            header.planes = static_cast<unsigned short>(1);
            header.bpp = static_cast<unsigned short>(image.getBits());
            header.compression = 0;
            header.imageSize = image.getSize();
            header.xPelsPerMeter = 0;
            header.yPelsPerMeter = 0;
            header.clrUsed = 0;
            header.clrImportantRotateAndReserved = 0;
        
            BGRdata = new unsigned char[image.getSize()];
            std::memcpy(BGRdata, image.getData(), image.getSize());
        
            try {
                Image::swapComponents(image.getWidth(), image.getHeight(), image.getBits(), BGRdata);
            } catch(const GLUL::Exception::InvalidArgument& exception) {
                GLUL::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
            }

            FILE *file = fopen(path.c_str(), "wb");
            if(!file) {
                delete[] BGRdata;
                GLUL::Log::LibraryStream().logError("Failed to open file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to open file: '" + path + "'");
            }

            if(fwrite(&headerData[2], 1, 54, file) != 54) {
                fclose(file);
                delete[] BGRdata;
                GLUL::Log::LibraryStream().logError("Failed to write header of BMP image file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to write header of BMP image file: '" + path + "'");
            }

            if(fwrite(BGRdata, 1, image.getSize(), file) != image.getSize()) {
                fclose(file);
                delete[] BGRdata;
                GLUL::Log::LibraryStream().logError("Failed to write BMP image's data to file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to write BMP image's data to file: '" + path + "'");
            }

            fclose(file);
            delete[] BGRdata;
        }

    }

}
