#include <Utils/Logger.h>
#include <Utils/Interfaces/Implementations/ImageFileBMP.h>


namespace Util {

    Image ImageFileBMP::read(const std::string& path) const throw(Util::Exception::InitializationFailed) {
        Image image;
        std::string error;
        unsigned char header[54];
        unsigned int dataOffset;
        unsigned int size;
        unsigned int width, height, bits;
        unsigned char* data;

        FILE *file = fopen(path.c_str(), "rb");
        if(!file) {
            image.reset();
            Util::Log::LibraryStream().logError("Failed to load image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to load image file: '" + path + "'");
        }

        if(fread(header, 1, 54, file) != 54) {
            image.reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Failed to read header of BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read header of BMP image file: '" + path + "'");
        }


        if(header[0] != 'B' || header[1] != 'M') {
            image.reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Input file is not a correct BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Input file is not a correct BMP image file: '" + path + "'");
        }

        if(header[0x1E] || header[0x1F] || header[0x20] || header[0x21]) {
            image.reset();
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
        size        = getUIntFromUCharArrayLE(&header[0x22]);
        width       = getUIntFromUCharArrayLE(&header[0x12]);
        height      = getUIntFromUCharArrayLE(&header[0x16]);
        bits        = getUIntFromUCharArrayLE(&header[0x1C]);

        if(size == 0)
            size = width * height * (bits / 8);

        if(dataOffset == 0)
            dataOffset = 54;

        data = new unsigned char[size];

        if(fread(data, 1, size, file) != size) {
            image.reset();
            fclose(file);
            Util::Log::LibraryStream().logError("Failed to read whole BMP image file: '" + path + "'");
            throw Exception::InitializationFailed("Failed to read whole BMP image file: '" + path + "'");
        }

        fclose(file);

        try {
            Image::swapComponents(width, height, bits, data);
        } catch(const Util::Exception::InvalidArgument& exception) {
            Util::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
        }

        // set image's member variables
        setImage(image, width, height, bits, data);

        return image;
    }

    void ImageFileBMP::save(const std::string& path) const throw(Util::Exception::InitializationFailed) {
        throw Util::Exception("ImageFileBMP::save(...) not yet implemented");
    }

}