#include <Utils/GL+/Buffer.h>

namespace GL {

    Buffer::Buffer() {
        create();
    }

    Buffer::Buffer(Target target, Usage usage) {
        create();

        setTarget(target);
        setUsage(usage);
    }

    Buffer::Buffer(Buffer&& buffer) {
        create();

        std::swap(_usage,    buffer._usage);
        std::swap(_target,   buffer._target);
        std::swap(_bufferID, buffer._bufferID);
    }

    Buffer::~Buffer() {
        destroy();
    }

    Buffer& Buffer::operator=(Buffer&& buffer) {
        std::swap(_usage,    buffer._usage);
        std::swap(_target,   buffer._target);
        std::swap(_bufferID, buffer._bufferID);

        return *this;
    }

    void Buffer::bind() const {
        glBindBuffer(static_cast<GLenum>(getTarget()), getID());
    }

    void Buffer::bind(Target target) {
        setTarget(target);
        bind();
    }

    void Buffer::unbind() const {
        glBindBuffer(static_cast<GLenum>(getTarget()), 0);
    }
    
    void Buffer::resize(GLsizeiptr size) {
        glBufferData(static_cast<GLenum>(getTarget()), size, nullptr, static_cast<GLenum>(getUsage()));
    }
    
    void Buffer::setData(const Data& data) {
        setData(data.size, data.data);
        setAttributes(data.pointers);
    }

    void Buffer::setData(GLsizeiptr size, const GLvoid* data) {
        glBufferData(static_cast<GLenum>(getTarget()), size, data, static_cast<GLenum>(getUsage()));
    }

    void Buffer::setData(GLsizeiptr size, const GLvoid* data, Usage usage) {
        setUsage(usage);
        glBufferData(static_cast<GLenum>(getTarget()), size, data, static_cast<GLenum>(getUsage()));
    }

    void Buffer::setSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
        glBufferSubData(static_cast<GLenum>(getTarget()), offset, size, data);
    }

    void Buffer::setUsage(Usage usage) {
        _usage = usage;
    }

    void Buffer::setTarget(Target target) {
        _target = target;
    }
    
    void Buffer::setAttributes(const std::list<VertexAttrib> attributes) {
        _attributePointers = attributes;
    }

    GLuint Buffer::getID() const {
        return _bufferID;
    }
    
    Buffer::Usage Buffer::getUsage() const {
        return _usage;
    }

    Buffer::Target Buffer::getTarget() const {
        return _target;
    }

    const std::list<VertexAttrib>& Buffer::getAttributes() const {
        return _attributePointers;
    }

    void Buffer::create() {
        glGenBuffers(1, &_bufferID);
    }

    void Buffer::destroy() {
        glDeleteBuffers(1, &_bufferID);
    }

}