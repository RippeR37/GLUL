#ifndef UTILS_GL_FRAMEBUFFER_H_INCLUDED
#define UTILS_GL_FRAMEBUFFER_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>

#include <stack>

namespace GL {

    class Framebuffer {
        public:
            Framebuffer();
            Framebuffer(Framebuffer&& framebuffer);
            ~Framebuffer();

            Framebuffer(const Framebuffer&) = delete;
            Framebuffer& operator=(const Framebuffer&) = delete;

            void bind() const;
            void unbind() const;

            GLuint getID() const;

        private:
            void create();
            void destroy();

            GLuint _framebufferID;
    };

}

#endif