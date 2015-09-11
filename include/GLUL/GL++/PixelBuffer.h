#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Buffer.h>
#include <GLUL/GL++/Texture.h>


namespace GL {

    class GLUL_API PixelBuffer : public GL::Buffer {
        public:
            enum class OperationType {
                Pack,
                Unpack
            };

            enum class DataFormat {
                Red          = GL_RED,
                Green        = GL_GREEN,
                Blue         = GL_BLUE,
                RG           = GL_RG,
                RGB          = GL_RGB,
                BGR          = GL_BGR,
                RGBA         = GL_RGBA,
                BGRA         = GL_BGRA,
                RedInt       = GL_RED_INTEGER,
                GreenInt     = GL_GREEN_INTEGER,
                BlueInt      = GL_BLUE_INTEGER,
                RGInt        = GL_RG_INTEGER,
                RGBInt       = GL_RGB_INTEGER,
                BGRInt       = GL_BGR_INTEGER,
                RGBAInt      = GL_RGBA_INTEGER,
                BGRAInt      = GL_BGRA_INTEGER,
                Depth        = GL_DEPTH_COMPONENT,
                Stencil      = GL_STENCIL_INDEX,
                DepthStencil = GL_DEPTH_STENCIL,
            };

            enum class DataType {
                Byte = GL_BYTE,
                uByte = GL_UNSIGNED_BYTE,
                Short = GL_SHORT,
                uShort = GL_UNSIGNED_SHORT,
                Int = GL_INT,
                uInt = GL_UNSIGNED_INT,
                Float = GL_FLOAT,
                uByte332 = GL_UNSIGNED_BYTE_3_3_2,
                uByte233R = GL_UNSIGNED_BYTE_2_3_3_REV,
                uShort565 = GL_UNSIGNED_SHORT_5_6_5,
                uShort565R = GL_UNSIGNED_SHORT_5_6_5_REV,
                uShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
                uShort4444R = GL_UNSIGNED_SHORT_4_4_4_4_REV,
                uShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
                uShort1555R = GL_UNSIGNED_SHORT_1_5_5_5_REV,
                uInt8888 = GL_UNSIGNED_INT_8_8_8_8,
                uInt8888R = GL_UNSIGNED_INT_8_8_8_8_REV,
                uInt1010102 = GL_UNSIGNED_INT_10_10_10_2,
                uInt2101010R = GL_UNSIGNED_INT_2_10_10_10_REV,
            };

            enum class TextureTarget {
                Tex1D = GL_TEXTURE_1D,
                Tex2D = GL_TEXTURE_2D,
                Tex3D = GL_TEXTURE_3D,
                Tex1DArray = GL_TEXTURE_1D_ARRAY,
                Tex2DArray = GL_TEXTURE_2D_ARRAY,
                TexRectangle = GL_TEXTURE_RECTANGLE,
                TexCubeXPos = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                TexCubeXNeg = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                TexCubeYPos = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                TexCubeYNeg = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                TexCubeZPos = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                TexCubeZNeg = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
            };

            typedef Texture::InternalFormat InternalFormat;

        public:
            PixelBuffer();
            PixelBuffer(OperationType operation, Usage usage = Usage::StaticCopy);
            PixelBuffer(PixelBuffer&& pbo);
            PixelBuffer(const PixelBuffer&) = delete;
            ~PixelBuffer();

            PixelBuffer& operator=(const PixelBuffer&) = delete;
            PixelBuffer& operator=(PixelBuffer&& pbo);

            void bind() const;
            void bind(OperationType operation);


            void getPixels(GLint x, GLint y, GLint width, GLint height, DataFormat format, DataType type, GLvoid* data);
            void getTexImage(TextureTarget target, GLint level, DataFormat format, DataType type, GLvoid* image);
            void getCompressedTexImage(TextureTarget target, GLint level, GLvoid* image);

            void setTexImage1D(GLint level, InternalFormat internalFormat, 
                GLsizei width, GLint border, DataFormat format, DataType type, const GLvoid* data);

            void setTexImage2D(GLint level, InternalFormat internalFormat, 
                GLsizei width, GLsizei height, GLint border, DataFormat format, DataType type, const GLvoid* data);

            void setTexImage3D(GLint level, InternalFormat internalFormat,
                GLsizei width, GLsizei height, GLsizei depth, GLint border, DataFormat format, DataType type, const GLvoid* data);


            void setTarget(OperationType operation);
            void setPacking(OperationType operation);

            Target getTarget() const;
            OperationType getOperation() const;

        private:
            OperationType _operation;

            using Buffer::setTarget;
    };

}
