#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Implementations/ImageFileTGA.h>

#include <cstring>


namespace GLUL {

    namespace Interface {

        Image ImageFileTGA::read(const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            Image image;
            unsigned int width, height, bits, size;
            unsigned char* data;

            std::ifstream fileStream;
            char buff[256];
            char c;
            char si_a[2];
            char* si = (char*)&si_a[0];
            int id_len, cm_type, type;
            int cm_len;
            unsigned int rowStride; // width * bits algined to 4bytes

            fileStream.open(path, std::fstream::binary);
            if(fileStream.is_open() == false) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Failed to load TGA image file: '" + path + "'");
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

            rowStride = Image::getAlignedRowSize(width, bits);
            size  = height * rowStride;

            if(type != 2 && type != 3) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
                throw Exception::InitializationFailed("Unsupported TGA format: '" + std::to_string(type) + "' in file: '" + path + "'");
            }

            if(bits != 24 && bits != 32) {
                image.reset();
                GLUL::Log::LibraryStream().logError("Unsupported TGA color bits: '" + std::to_string(bits) + "' in file: '" + path + "'");
                throw Exception::InitializationFailed("Unsupported TGA color bits: '" + std::to_string(bits) + "' in file: '" + path + "'");
            }

            if(id_len > 0)
                fileStream.read(buff, id_len);

            if(cm_type != 0 && cm_len > 0)
                fileStream.read(buff, cm_len);

            data = new unsigned char[size];

            for(unsigned int rowPtr = 0; rowPtr < size; rowPtr += rowStride)
                fileStream.read((char*)(data + rowPtr), width * (bits / 8));

            fileStream.close();

            try {
                Image::swapComponents(width, height, bits, data);
            } catch(const GLUL::Exception::InvalidArgument& exception) {
                GLUL::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
            }

            // set image's member variables
            setImage(image, width, height, bits, data);

            return image;
        }

        void ImageFileTGA::save(const Image& image, const std::string& path) const throw(GLUL::Exception::InitializationFailed) {
            std::ofstream fileStream;
            unsigned int rowStride; // width * bits algined to 4bytes
            unsigned short int w = static_cast<unsigned short>(image.getWidth());
            unsigned short int h = static_cast<unsigned short>(image.getHeight());
            unsigned char b = static_cast<unsigned char>(image.getBits());
            unsigned char d; // image descriptor
            unsigned char c;
            unsigned char* BGRdata;

            union unionCharShort {
                unsigned char c[2];
                unsigned short s;
            } u;

            rowStride = Image::getAlignedRowSize(image.getWidth(), image.getBits());
            d = (image.getBits() == 32 ? 8 : 0);

            BGRdata = new unsigned char[image.getSize()];
            std::memcpy(BGRdata, image.getData(), image.getSize());
        
            try {
                Image::swapComponents(image.getWidth(), image.getHeight(), image.getBits(), BGRdata);
            } catch(const GLUL::Exception::InvalidArgument& exception) {
                GLUL::Log::LibraryStream().logWarning(exception.what() + std::string(" for image '" + path + "'"));
            }

            fileStream.open(path, std::fstream::binary);
            if(fileStream.is_open() == false) {
                GLUL::Log::LibraryStream().logError("Failed to open file: '" + path + "'");
                throw Exception::InitializationFailed("Failed to load file: '" + path + "'");
            }

            c = 0;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // id_len [BYTE]
            c = 0;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // cm_type [BYTE]
            c = 2;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // type [BYTE]

            u.s = 0;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // cm_index [SHORT]
            u.s = 0;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // cm_len [SHORT]
            c = 0;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // cm_bpp [BYTE]
        
            u.s = 0;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // x_or [SHORT]
            u.s = 0;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // y_or [SHORT]
            u.s = w;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // width [SHORT]
            u.s = h;    fileStream.write(reinterpret_cast<char*>(&u.c), 2); // height [SHORT]
            c = b;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // bpp [BYTE]
            c = d;      fileStream.write(reinterpret_cast<char*>(&c), 1);   // img_descriptor [BYTE]

            // Writing data without 4byte alignment
            for(unsigned int rowPtr = 0; rowPtr < image.getSize(); rowPtr += rowStride)
                fileStream.write(reinterpret_cast<char*>(BGRdata + rowPtr), image.getWidth() * (image.getBits() / 8));

            // Writing footera data
            int zeroInt = 0;
            char signature[18];
            std::strcpy(signature, "TRUEVISION-XFILE.");

            fileStream.write(reinterpret_cast<char*>(&zeroInt), 4);     // extensions offset [INT]
            fileStream.write(reinterpret_cast<char*>(&zeroInt), 4);     // dev area offset [INT]
            fileStream.write(reinterpret_cast<char*>(signature), 18);   // signature

            fileStream.close();
        }

    }

}
