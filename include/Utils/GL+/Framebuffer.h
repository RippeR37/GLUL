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
            Framebuffer(const Framebuffer&) = delete;
            ~Framebuffer();

            Framebuffer& operator=(const Framebuffer&) = delete;
            Framebuffer& operator=(Framebuffer&& framebuffer);

            void create();
            void destroy();

            void bind() const;
            void unbind() const;

            GLuint getID() const;

        private:
            bool isCreated() const;

            bool _isCreated;
            GLuint _framebufferID;
    };

}

#endif