#pragma once

#include <GLUL/GL++/Buffer.h>


namespace GL {

    template<typename T>
    void Buffer::setData(const std::vector<T>& data) {
        glBufferData(static_cast<GLenum>(getTarget()), data.size() * sizeof(T), data.data(), static_cast<GLenum>(getUsage()));
    }

    template<typename T>
    void Buffer::setData(const std::vector<T>& data, Usage usage) {
        setUsage(usage);
        setData(data);
    }

    template<typename T>
    void Buffer::setSubData(const std::vector<T>& data, GLintptr offset) {
        setSubData(data, offset, data.size() * sizeof(T));
    }

    template<typename T>
    void Buffer::setSubData(const std::vector<T>& data, GLintptr offset, GLsizeiptr size) {
        glBufferSubData(static_cast<GLenum>(getTarget()), offset, size, &data.data());
    }

}
