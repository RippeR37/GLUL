#include <GLUL/GL++/VertexAttrib.h>


namespace GL {
    
    VertexAttrib::VertexAttrib() {
        index = 0;
        size = 0;
        type = GL_FLOAT;
        normalized = GL_FALSE;
        stride = 0;
        offset = nullptr;
    }

    VertexAttrib::VertexAttrib(GLuint index_, GLint size_, GLenum type_, GLsizei stride_, GLvoid* offset_) {
        index = index_;
        size = size_;
        type = type_;
        normalized = GL_FALSE;
        stride = stride_;
        offset = offset_;
    }

    VertexAttrib::~VertexAttrib() {

    }

    void VertexAttrib::set() {
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
    }

}
