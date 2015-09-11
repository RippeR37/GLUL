#pragma once

#include <GLUL/Config.h>
#include <GLUL/Image.h>
#include <GLUL/Exception.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <utility>
#include <string>
#include <list>


namespace GL {

    class GLUL_API Texture {
        public:
            enum class Target {
                Tex1D = GL_TEXTURE_1D,
                Tex2D = GL_TEXTURE_2D, 
                Tex3D = GL_TEXTURE_3D, 
                Tex1DArray = GL_TEXTURE_1D_ARRAY, 
                Tex2DArray = GL_TEXTURE_2D_ARRAY, 
                TexRectangle = GL_TEXTURE_RECTANGLE, 
                TexCubeMap = GL_TEXTURE_CUBE_MAP, 
                TexCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY, 
                TexBuffer = GL_TEXTURE_BUFFER, 
                Tex2DMS = GL_TEXTURE_2D_MULTISAMPLE, 
                Tex2DMSArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
            };

            enum class Format {
                Red = GL_RED,
                RG  = GL_RG,
                RGB = GL_RGB,
                BGR = GL_BGR,
                RGBA = GL_RGBA,
                BGRA = GL_BGRA,
                RedInt = GL_RED_INTEGER,
                RGInt  = GL_RG_INTEGER,
                RGBInt = GL_RGB_INTEGER,
                BGRInt = GL_BGR_INTEGER,
                RGBAInt = GL_RGBA_INTEGER,
                BGRAInt = GL_BGRA_INTEGER,
                StencilIndex = GL_STENCIL_INDEX,
                DepthStencil = GL_DEPTH_STENCIL,
                DepthComponent = GL_DEPTH_COMPONENT,

                DefaultFormat,
            };

            enum class InternalFormat {
                Red = GL_RED,
                RG  = GL_RG,
                RGB = GL_RGB,
                RGBA = GL_RGBA,
                R8 = GL_R8,
                R16 = GL_R16,
                RG8 = GL_RG8,
                RG16 = GL_RG16,
                R3G3B2 = GL_R3_G3_B2,
                RGB4 = GL_RGB4,
                RGB5 = GL_RGB5,
                RGB8 = GL_RGB8,
                RGB10 = GL_RGB10,
                RGB12 = GL_RGB12,
                RGBA2 = GL_RGBA2,
                RGBA4 = GL_RGBA4,
                RGB5A1 = GL_RGB5_A1,
                RGBA8 = GL_RGBA8,
                RGB10A2 = GL_RGB10_A2,
                RGB10A2u = GL_RGB10_A2UI,
                RGBA12 = GL_RGBA12,
                RGBA16 = GL_RGBA16,
                SRGB8 = GL_SRGB8,
                R16f = GL_R16F,
                RG16f = GL_RG16F,
                RGB16f = GL_RGB16F,
                RGBA16f = GL_RGBA16F,
                R32f = GL_R32F,
                RG32f = GL_RG32F,
                RGB32f = GL_RGB32F,
                RGBA32f = GL_RGBA32F,
                R11G11B10f = GL_R11F_G11F_B10F,
                RGB9E5 = GL_RGB9_E5,
                R8i = GL_R8I,
                R8u = GL_R8UI,
                R16i = GL_R16I,
                R16u = GL_R16UI,
                R32i = GL_R32I,
                R32u = GL_R32UI,
                RG8i = GL_RG8I,
                RG8u = GL_RG8UI,
                RG16i = GL_RG16I,
                RG16u = GL_RG16UI,
                RG32i = GL_RG32I,
                RG32u = GL_RG32UI,
                RGB8i = GL_RGB8I,
                RGB8u = GL_RGB8UI,
                RGB16i = GL_RGB16I,
                RGB16u = GL_RGB16UI,
                RGB32i = GL_RGB32I,
                RGB32u = GL_RGB32UI,
                RGBA8i = GL_RGBA8I,
                RGBA8u = GL_RGBA8UI,
                RGBA16i = GL_RGBA16I,
                RGBA16u = GL_RGBA16UI,
                RGBA32i = GL_RGBA32I,
                RGBA32u = GL_RGBA32UI,
                DepthStencil = GL_DEPTH_STENCIL,
                DepthComponent = GL_DEPTH_COMPONENT,

                DefaultFormat,
            };

        public:
            Texture();

            Texture(const GLUL::Image& image, Target target = Target::Tex2D, 
                Format format = Format::DefaultFormat, InternalFormat internalFormat = InternalFormat::DefaultFormat);

            Texture(const std::string& path, Target target = Target::Tex2D, 
                Format format = Format::DefaultFormat, InternalFormat internalFormat = InternalFormat::DefaultFormat) 
                throw(GLUL::Exception::InitializationFailed, GLUL::Exception::FatalError);

            Texture(Texture&& texture);
            Texture(const Texture&) = delete;
            ~Texture();

            Texture& operator=(const Texture&) = delete;
            Texture& operator=(Texture&& texture);

            void create();
            void destroy();

            void bind() const;
            void unbind() const;

            void load(const GLUL::Image& image, Target target = Target::Tex2D, 
                Format format = Format::DefaultFormat, InternalFormat internalFormat = InternalFormat::DefaultFormat) throw(GLUL::Exception::FatalError);

            void generateMipmap();

            void setData1D(GLsizei width, GLenum dataType, const GLvoid* data, GLint level = 0);
            void setData2D(GLsizei width, GLsizei height, GLenum dataType, const GLvoid* data, GLint level = 0);
            void setData3D(GLsizei width, GLsizei height, GLsizei depth, GLenum dataType, const GLvoid* data, GLint level = 0);

            void setTarget(Target target);
            void setFormat(Format format);
            void setInternalFromat(InternalFormat format);

            void setParameters();
            void setParameters(std::list<std::pair<GLenum, GLint>> parameters);
            void setParameters(std::list<std::pair<GLenum, GLfloat>> parameters);

            bool isAlpha() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            Target getTarget() const;
            Format getFormat() const;
            InternalFormat getInternalFromat() const;
            GLuint getID() const;

        private:
            void assingData2D(const GLUL::Image& image, const Format format, const InternalFormat internalFormat) throw(GLUL::Exception::FatalError);

            void setWidth(unsigned int width);
            void setHeight(unsigned int height);

            bool isCreated() const;


            bool _isAlpha;
            bool _isCreated;
            unsigned int _width;
            unsigned int _height;
            GLuint _textureID;

            Target _target;
            Format _format;
            InternalFormat _internalFormat;
    };

}
