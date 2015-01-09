#include <Utils/GL+/Texture.h>

namespace GL {
    
    Texture::Texture() {
        create();
    }

    Texture::Texture(const Util::Image& image, Target target, Format format, InternalFormat internalFormat) {
        create();

        load(image, target, format, internalFormat);
    }

    Texture::Texture(const std::string& path, Target target, Format format, InternalFormat internalFormat) {
        create();

        Util::Image image(path, Util::Image::Format::BMP);
        load(image, target, format, internalFormat);
    }
    
    Texture::Texture(Texture&& texture) {
        create();

        std::swap(_isAlpha, texture._isAlpha);
        std::swap(_width, texture._width);
        std::swap(_height, texture._height);
        std::swap(_target, texture._target);
        std::swap(_textureID, texture._textureID);
        std::swap(_format, texture._format);
        std::swap(_internalFormat, texture._internalFormat);
    }

    Texture::~Texture() {
        destroy();
    }

    Texture& Texture::operator=(Texture&& texture) {
        std::swap(_isAlpha, texture._isAlpha);
        std::swap(_width, texture._width);
        std::swap(_height, texture._height);
        std::swap(_target, texture._target);
        std::swap(_textureID, texture._textureID);
        std::swap(_format, texture._format);
        std::swap(_internalFormat, texture._internalFormat);

        return *this;
    }

    void Texture::bind() const {
        glBindTexture(static_cast<GLenum>(getTarget()), getID());
    }

    void Texture::unbind() const {
        glBindTexture(static_cast<GLenum>(getTarget()), 0);
    }

    void Texture::load(const Util::Image& image, Target target, Format format, InternalFormat internalFormat) {
        setTarget(target);
        bind();
        assingData(image, format, internalFormat);
        setParameters();
        generateMipmap();
        unbind();
    }

    void Texture::generateMipmap() {
        glGenerateMipmap(static_cast<GLenum>(getTarget()));
    }

    void Texture::setData1D(GLsizei width, GLenum dataType, const GLvoid* data, GLint level) {
        setWidth(width);

        glTexImage1D(
            static_cast<GLenum>(getTarget()), 
            level, 
            static_cast<GLenum>(getInternalFromat()), 
            width, 
            0, 
            static_cast<GLenum>(getFormat()), 
            dataType, 
            data
        );
    }

    void Texture::setData2D(GLsizei width, GLsizei height, GLenum dataType, const GLvoid* data, GLint level) {
        setWidth(width);
        setHeight(height);

        glTexImage2D(
            static_cast<GLenum>(getTarget()), 
            level, 
            static_cast<GLenum>(getInternalFromat()), 
            width, 
            height,
            0, 
            static_cast<GLenum>(getFormat()), 
            dataType, 
            data
        );
    }

    void Texture::setData3D(GLsizei width, GLsizei height, GLsizei depth, GLenum dataType, const GLvoid* data, GLint level) {
        setWidth(width);
        setHeight(height);

        glTexImage3D(
            static_cast<GLenum>(getTarget()), 
            level, 
            static_cast<GLenum>(getInternalFromat()), 
            width, 
            height,
            height,
            0, 
            static_cast<GLenum>(getFormat()), 
            dataType, 
            data
        );
    }
    
    void Texture::setTarget(Target target) {
        _target = target;
    }
    
    void Texture::setParameters() {
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(static_cast<GLenum>(getTarget()), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    void Texture::setParametersI(std::list<std::pair<GLenum, GLint>> parameters) {
        for(auto& parameter : parameters)
            glTexParameteri(static_cast<GLenum>(getTarget()), parameter.first, parameter.second);
    }

    void Texture::setParametersF(std::list<std::pair<GLenum, GLfloat>> parameters) {
        for(auto& parameter : parameters)
            glTexParameterf(static_cast<GLenum>(getTarget()), parameter.first, parameter.second);
    }

    void Texture::setFormat(Format format) {
        _format = format;
    }

    void Texture::setInternalFromat(InternalFormat format) {
        _internalFormat = format;
    }

    bool Texture::isAlpha() const {
        return _isAlpha;
    }

    unsigned int Texture::getWidth() const {
        return _width;
    }

    unsigned int Texture::getHeight() const {
        return _height;
    }

    Texture::Target Texture::getTarget() const {
        return _target;
    }

    Texture::Format Texture::getFormat() const {
        return _format;
    }
    
    Texture::InternalFormat Texture::getInternalFromat() const {
        return _internalFormat;
    }

    GLuint Texture::getID() const {
        return _textureID;
    }

    void Texture::create() {
        glGenTextures(1, &_textureID);

        setWidth(0);
        setHeight(0);
    }

    void Texture::destroy() {
        glDeleteTextures(1, &_textureID);
    }

    void Texture::assingData(const Util::Image& image, const Format format, const InternalFormat internalFormat) {
        if(format == Format::DefaultFormat) {
            switch(image.getBits()) {
                case 24: 
                    setInternalFromat(InternalFormat::RGB);
                    setFormat(Format::BGR);
                    break;

                case 32:
                    setInternalFromat(InternalFormat::RGBA);
                    setFormat(Format::BGRA);
                    break;

                default:
                    throw Util::Exception::FatalError("Could not determine texture's color profile");
                    break;
            }

        } else {
            setFormat(format);
            setInternalFromat(internalFormat);
        }

        setData2D(image.getWidth(), image.getHeight(), GL_UNSIGNED_INT, image.getData());
    }
    
    void Texture::setWidth(unsigned int width) {
        _width = width;
    }

    void Texture::setHeight(unsigned int height) {
        _height = height;
    }

}