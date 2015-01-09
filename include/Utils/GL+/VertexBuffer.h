#ifndef UTILS_GL_VERTEX_BUFFER_H_INCLUDED
#define UTILS_GL_VERTEX_BUFFER_H_INCLUDED

#include "VertexAttrib.h"
#include "../Exception.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <list>
#include <vector>
#include <functional>

namespace GL {

    class VertexBuffer {
        public:
            enum class Usage {
                StaticDraw  = GL_STATIC_DRAW,
                StaticRead  = GL_STATIC_READ,
                StaticCopy  = GL_STATIC_COPY,
                DynamicDraw = GL_DYNAMIC_DRAW,
                DynamicRead = GL_DYNAMIC_READ,
                DynamicCopy = GL_DYNAMIC_COPY,
                StreamDraw  = GL_STREAM_DRAW,
                StreamRead  = GL_STREAM_READ,
                StreamCopy  = GL_STREAM_COPY,
            };

            enum class Target {
                Array               = GL_ARRAY_BUFFER,
                AtomicCounter       = GL_ATOMIC_COUNTER_BUFFER,
                CopyRead            = GL_COPY_READ_BUFFER,
                CopyWrite           = GL_COPY_WRITE_BUFFER,
                DispatchIndirect    = GL_DISPATCH_INDIRECT_BUFFER,
                DrawIndirect        = GL_DRAW_INDIRECT_BUFFER,
                ElementArray        = GL_ELEMENT_ARRAY_BUFFER,
                PixelPack           = GL_PIXEL_PACK_BUFFER,
                PixelUnpack         = GL_PIXEL_UNPACK_BUFFER,
                Query               = GL_QUERY_BUFFER,
                ShaderStorage       = GL_SHADER_STORAGE_BUFFER,
                Texture             = GL_TEXTURE_BUFFER,
                TransformFeedback   = GL_TRANSFORM_FEEDBACK_BUFFER,
                Uniform             = GL_UNIFORM_BUFFER,
            };

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
            VertexBuffer(Target target, Usage usage = Usage::StaticDraw);
            VertexBuffer(VertexBuffer&& vbo);
            ~VertexBuffer();

            VertexBuffer& operator=(VertexBuffer&& vbo);

            void bind() const;
            void bind(Target target);
            void unbind() const;

            void resize(GLsizeiptr size);

            void setData(const Data& data);
            void setData(GLsizeiptr size, const GLvoid* data);
            void setData(GLsizeiptr size, const GLvoid* data, Usage usage);
            void setSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
            
            void setUsage(Usage usage);
            void setTarget(Target target);
            void setAttributes(const std::list<VertexAttrib> attributes);

            GLuint getID() const;
            Usage  getUsage() const;
            Target getTarget() const;
            const std::list<VertexAttrib>& getAttributes() const;

        public:
            template<typename T> 
            void setData(const std::vector<T>& data);

            template<typename T> 
            void setData(const std::vector<T>& data, Usage usage);

            template<typename T> 
            void setSubData(const std::vector<T>& data, GLintptr offset);

            template<typename T> 
            void setSubData(const std::vector<T>& data, GLintptr offset, GLsizeiptr size);

        private:
            VertexBuffer& operator=(const VertexBuffer&);
            VertexBuffer(const VertexBuffer&);

            void create();
            void destroy();
            
            std::list<VertexAttrib> _attributePointers;

            Usage _usage;
            GLuint _vboID;
            Target _target;
    };

}

#include "VertexBuffer.hpp"

#endif