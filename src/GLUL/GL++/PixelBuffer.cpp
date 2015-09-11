#include <GLUL/GL++/PixelBuffer.h>


namespace GL {

    PixelBuffer::PixelBuffer() : Buffer(Target::PixelPack) {
        setPacking(OperationType::Pack);
    }

    PixelBuffer::PixelBuffer(OperationType operation, Usage usage) : Buffer(Target::PixelPack, usage) {
        setPacking(operation);
    }

    PixelBuffer::PixelBuffer(PixelBuffer&& pbo) : Buffer(std::move(pbo)) {
        std::swap(_operation, pbo._operation);
    }

    PixelBuffer::~PixelBuffer() {

    }

    PixelBuffer& PixelBuffer::operator=(PixelBuffer&& pbo) {
        std::swap(_usage, pbo._usage);
        std::swap(_target, pbo._target);
        std::swap(_bufferID, pbo._bufferID);
        std::swap(_operation, pbo._operation);
        std::swap(_isCreated, pbo._isCreated);

        return *this;
    }

    void PixelBuffer::bind() const {
        Buffer::bind();
    }

    void PixelBuffer::bind(OperationType operation) {
        setPacking(operation);
        bind();
    }


    void PixelBuffer::getPixels(GLint x, GLint y, GLint width, GLint height, DataFormat format, DataType type, GLvoid* data) {
        glReadPixels(x, y, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void PixelBuffer::getTexImage(TextureTarget target, GLint level, DataFormat format, DataType type, GLvoid* image) {
        glGetTexImage(static_cast<GLenum>(target), level, static_cast<GLenum>(format), static_cast<GLenum>(type), image);
    }

    void PixelBuffer::getCompressedTexImage(TextureTarget target, GLint level, GLvoid* image) {
        glGetCompressedTexImage(static_cast<GLenum>(target), level, image);
    }

    void PixelBuffer::setTexImage1D(GLint level, InternalFormat internalFormat, GLsizei width, GLint border, DataFormat format, DataType type, const GLvoid* data) {
        glTexImage1D(GL_TEXTURE_1D, level, static_cast<GLenum>(internalFormat), width, border, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void PixelBuffer::setTexImage2D(GLint level, InternalFormat internalFormat, GLsizei width, GLsizei height, GLint border, DataFormat format, DataType type, const GLvoid* data) {
        glTexImage2D(GL_TEXTURE_1D, level, static_cast<GLenum>(internalFormat), width, height, border, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void PixelBuffer::setTexImage3D(GLint level, InternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, DataFormat format, DataType type, const GLvoid* data) {
        glTexImage3D(GL_TEXTURE_1D, level, static_cast<GLenum>(internalFormat), width, height, depth, border, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }


    void PixelBuffer::setTarget(OperationType operation) {
        _operation = operation;

        if(operation == OperationType::Pack)
            Buffer::setTarget(Target::PixelPack);
        else
            Buffer::setTarget(Target::PixelUnpack);
    }

    void PixelBuffer::setPacking(OperationType operation) {
        setTarget(operation);
    }

    Buffer::Target PixelBuffer::getTarget() const {
        if(_operation == OperationType::Pack)
            return Target::PixelPack;
        else
            return Target::PixelUnpack;
    }

    PixelBuffer::OperationType PixelBuffer::getOperation() const {
        return _operation;
    }

}
