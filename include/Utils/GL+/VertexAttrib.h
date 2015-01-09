#ifndef UTILS_GL_VERTEX_ATTRIB_H_INCLUDED
#define UTILS_GL_VERTEX_ATTRIB_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GL {

    class VertexAttrib {
        public:
            VertexAttrib();
            VertexAttrib(GLuint index_, GLint size_, GLenum type_, GLsizei stride_, GLvoid* offset_);
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

#endif