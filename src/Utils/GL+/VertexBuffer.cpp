#include <Utils/GL+/VertexBuffer.h>

namespace GL {

    VertexBuffer::VertexBuffer() {
        create();
    }

    VertexBuffer::VertexBuffer(Target target, Usage usage) {
        setTarget(target);
        setUsage(usage);
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vbo) {
        create();

        std::swap(_usage, vbo._usage);
        std::swap(_vboID, vbo._vboID);
        std::swap(_target, vbo._target);
    }

    VertexBuffer::~VertexBuffer() {
        destroy();
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vbo) {
        std::swap(_usage, vbo._usage);
        std::swap(_vboID, vbo._vboID);
        std::swap(_target, vbo._target);

        return *this;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(static_cast<GLenum>(getTarget()), _vboID);
    }

    void VertexBuffer::bind(Target target) {
        setTarget(target);
        bind();
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(static_cast<GLenum>(getTarget()), 0);
    }
    
    void VertexBuffer::resize(GLsizeiptr size) {
        glBufferData(static_cast<GLenum>(getTarget()), size, nullptr, static_cast<GLenum>(getUsage()));
    }
    
    void VertexBuffer::setData(const Data& data) {
        setData(data.size, data.data);
        setAttributes(data.pointers);
    }

    void VertexBuffer::setData(GLsizeiptr size, const GLvoid* data) {
        glBufferData(static_cast<GLenum>(getTarget()), size, data, static_cast<GLenum>(getUsage()));
    }

    void VertexBuffer::setData(GLsizeiptr size, const GLvoid* data, Usage usage) {
        setUsage(usage);
        glBufferData(static_cast<GLenum>(getTarget()), size, data, static_cast<GLenum>(getUsage()));
    }

    void VertexBuffer::setSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
        glBufferSubData(static_cast<GLenum>(getTarget()), offset, size, data);
    }

    void VertexBuffer::setUsage(Usage usage) {
        _usage = usage;
    }

    void VertexBuffer::setTarget(Target target) {
        _target = target;
    }
    
    void VertexBuffer::setAttributes(const std::list<VertexAttrib> attributes) {
        _attributePointers = attributes;
    }

    GLuint VertexBuffer::getID() const {
        return _vboID;
    }
    
    VertexBuffer::Usage VertexBuffer::getUsage() const {
        return _usage;
    }

    VertexBuffer::Target VertexBuffer::getTarget() const {
        return _target;
    }

    const std::list<VertexAttrib>& VertexBuffer::getAttributes() const {
        return _attributePointers;
    }

    void VertexBuffer::create() {
        glGenBuffers(1, &_vboID);
    }

    void VertexBuffer::destroy() {
        glDeleteBuffers(1, &_vboID);
    }

}