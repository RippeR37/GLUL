#ifndef UTILS_GL_VERTEX_BUFFER_HPP_INCLUDED
#define UTILS_GL_VERTEX_BUFFER_HPP_INCLUDED

#include <Utils/GL+/VertexBuffer.h>

namespace GL {

    template<typename T>
    void VertexBuffer::setData(const std::vector<T>& data) {
        glBufferData(static_cast<GLenum>(getTarget()), data.size() * sizeof(T), &data[0], static_cast<GLenum>(getUsage()));
    }

    template<typename T>
    void VertexBuffer::setData(const std::vector<T>& data, Usage usage) {
        setUsage(usage);
        setData(data);
    }

    template<typename T>
    void VertexBuffer::setSubData(const std::vector<T>& data, GLintptr offset) {
        setSubData(data, offset, data.size() * sizeof(T));
    }

    template<typename T>
    void VertexBuffer::setSubData(const std::vector<T>& data, GLintptr offset, GLsizeiptr size) {
        glBufferSubData(static_cast<GLenum>(getTarget()), offset, size, &data[0]);
    }

}

#endif