#include <Utils/Logger.h>
#include <Utils/Interfaces/Implementations/ImageFileTGA.h>


namespace Util {

    Image ImageFileTGA::read(const std::string& path) const throw(Util::Exception::InitializationFailed) {
        Image image;
        unsigned int width, height, bits, size;
        unsigned char* data;

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
            image.reset();
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
        fileStream.read(si, 2);         width  = (si[1] << 8) | si[0];
        fileStream.read(si, 2);         height = (si[1] << 8) | si[0];
        fileStream.read(&c, 1);         bits = (int)c;
        fileStream.read(&c, 1);         // img descriptor

        c_mode = bits / 8;
        size  = width * height * c_mode;

        if(type != 2 && type != 3) {
            image.reset();
            Util::Log::LibraryStream().logError("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
        }

        if(c_mode != 3 && c_mode != 4) {
            image.reset();
            Util::Log::LibraryStream().logError("Unsupported TGA color bits: '" + std::to_string(c_mode) + "' in file: '" + path + "'");
            throw Exception::InitializationFailed("Unsupported TGA color bits: '" + std::to_string(c_mode) + "' in file: '" + path + "'");
        }

        if(id_len > 0)
            fileStream.read(buff, id_len);
        if(cm_type != 0 && cm_len > 0)
            fileStream.read(buff, cm_len);

        data = new unsigned char[size];
        fileStream.read((char*)data, size);
        fileStream.close();

        try {
            Image::swapComponents(width, height, bits, data);
        } catch(const Util::Exception::InvalidArgument& exception) {
            Util::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
        }

        // set image's member variables
        setImage(image, width, height, bits, data);

        return image;
    }

    void ImageFileTGA::save(const Image& image, const std::string& path) const throw(Util::Exception::InitializationFailed) {
        throw Util::Exception("ImageFileTGA::save(...) not yet implemented");
    }

}