#ifndef UTILS_GL_VERTEX_BUFFER_H_INCLUDED
#define UTILS_GL_VERTEX_BUFFER_H_INCLUDED

#include <Utils/GL+/Buffer.h>
#include <Utils/GL+/VertexAttrib.h>

#include <list>

namespace GL {

    class VertexBuffer : public GL::Buffer {
        public:
            class Data {
                public:
                    Data() : data(nullptr), size(0) { }
                    Data(GLvoid* data_, GLsizeiptr size_) : data(data), size(size_) { }

                    GLvoid*    data;
                    GLsizeiptr size;
                    std::list<VertexAttrib> pointers;
            };
        
        public:
            VertexBuffer();
            VertexBuffer(Usage usage);
            VertexBuffer(VertexBuffer&& vbo);
            ~VertexBuffer();

            VertexBuffer(const VertexBuffer&) = delete;
            VertexBuffer& operator=(const VertexBuffer&) = delete;

            VertexBuffer& operator=(VertexBuffer&& vbo);

            void bind() const;

            void setData(const VertexBuffer::Data& data);

            void setTarget();
            void setAttributes(const std::list<VertexAttrib> attributes);

            Target getTarget() const;
            const std::list<VertexAttrib>& getAttributes() const;

        private:
            std::list<VertexAttrib> _attributePointers;

        public: 
            using Buffer::setData;
    };

}

#endif