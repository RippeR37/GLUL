#ifndef UTILS_GL_PIXEL_BUFFER_H_INCLUDED
#define UTILS_GL_PIXEL_BUFFER_H_INCLUDED

#include <Utils/GL+/Buffer.h>

namespace GL {

    class PixelBuffer : public GL::Buffer {
        public:
            enum class Packing {
                Pack,
                Unpack
            };

        public:
            PixelBuffer();
            PixelBuffer(Packing packing, Usage usage = Usage::StaticCopy);
            PixelBuffer(PixelBuffer&& pbo);
            ~PixelBuffer();

            PixelBuffer(const PixelBuffer&) = delete;
            PixelBuffer& operator=(const PixelBuffer&) = delete;

            PixelBuffer& operator=(PixelBuffer&& pbo);

            void bind() const;
            void bind(Packing packing);

            void readPixels(GLint x, GLint y, GLint width, GLint height, GLenum format, GLvoid* data);
            void getTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* image);
            void getTexCompressedImage(GLenum target, GLint level, GLvoid* image);

            void setTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data);
            void setTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
            void setTexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data);

            /*
            void setTexSubImage1D();
            void setTexSubImage2D();
            void setTexSubImage3D();

            void setTexCompressedImage1D();
            void setTexCompressedImage2D();
            void setTexCompressedImage3D();

            void setTexCompressedSubImage1D();
            void setTexCompressedSubImage2D();
            void setTexCompressedSubImage2D();
            */

            void setTarget(Packing packing);
            void setPacking(Packing packing);

            Target getTarget() const;
            Packing getPacking() const;

        private:
            Packing _packing;
    };

}

#endif