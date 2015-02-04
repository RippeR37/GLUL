#ifndef UTILS_GL_VERTEX_BUFFER_H_INCLUDED
#define UTILS_GL_VERTEX_BUFFER_H_INCLUDED

#include <Utils/GL+/Buffer.h>

namespace GL {

    class VertexBuffer : public GL::Buffer {
        public:
            VertexBuffer();
            VertexBuffer(Usage usage);
            VertexBuffer(VertexBuffer&& vbo);
            ~VertexBuffer();

            VertexBuffer(const VertexBuffer&) = delete;
            VertexBuffer& operator=(const VertexBuffer&) = delete;

            VertexBuffer& operator=(VertexBuffer&& vbo);

            void bind() const;

            void setTarget();

            Target getTarget() const;
    };

}

#include "Buffer.hpp"

#endif