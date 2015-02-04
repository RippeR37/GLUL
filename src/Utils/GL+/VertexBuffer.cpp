#include <Utils/GL+/VertexBuffer.h>

namespace GL {

    VertexBuffer::VertexBuffer() : Buffer(Target::Array) {

    }

    VertexBuffer::VertexBuffer(Usage usage) : Buffer(Target::Array, usage) {
         
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vbo) : Buffer(std::move(vbo)) {

    }

    VertexBuffer::~VertexBuffer() {

    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vbo) {
        std::swap(_usage,    vbo._usage);
        std::swap(_target,   vbo._target);
        std::swap(_bufferID, vbo._bufferID);

        return *this;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(static_cast<GLenum>(Buffer::Target::Array), getID());
    }

    void VertexBuffer::setTarget() {
        _target = Target::Array;
    }

    Buffer::Target VertexBuffer::getTarget() const {
        return Target::Array;
    }

}
