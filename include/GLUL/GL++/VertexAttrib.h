#pragma once

#include <GLUL/Config.h>

#include <GL/glew.h>

#include <cstddef>


namespace GL {

    class GLUL_API VertexAttrib {
        public:
            VertexAttrib();
            VertexAttrib(GLuint index_, GLint size_, GLenum type_, GLsizei stride_, GLvoid* offset_);
            VertexAttrib(GLuint index_, GLint size_, GLenum type_, GLsizei stride_, std::size_t offset_);
            ~VertexAttrib();

            void set();
        
        public:
            GLuint index;
            GLint  size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid* offset;
    };

}
