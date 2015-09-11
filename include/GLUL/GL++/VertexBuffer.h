#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Buffer.h>
#include <GLUL/GL++/VertexAttrib.h>

#include <list>


namespace GL {

    class GLUL_API VertexBuffer : public GL::Buffer {
        public:
            class GLUL_API Data {
                public:
                    Data() : data(nullptr), size(0) { }
                    Data(GLvoid* data_, GLsizeiptr size_) : data(data_), size(size_) { }

                    GLvoid*    data;
                    GLsizeiptr size;
                    std::list<VertexAttrib> pointers;
            };
        
        public:
            VertexBuffer();
            VertexBuffer(Usage usage);
            VertexBuffer(VertexBuffer&& vbo);
            VertexBuffer(const VertexBuffer&) = delete;
            ~VertexBuffer();

            VertexBuffer& operator=(const VertexBuffer&) = delete;
            VertexBuffer& operator=(VertexBuffer&& vbo);

            void bind() const;

            void setData(const VertexBuffer::Data& data);

            void setTarget();
            void setAttributes(const std::list<VertexAttrib>& attributes);

            Target getTarget() const;
            const std::list<VertexAttrib>& getAttributes() const;

            using Buffer::setData;

        private:
            std::list<VertexAttrib> _attributePointers;

            using Buffer::setTarget;
    };

}
