#ifndef UTILS_GL_CONTEXT_H_INCLUDED
#define UTILS_GL_CONTEXT_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

namespace Util {
    class Window;
}

namespace GL {

    class Context {
        public:
            enum class BufferMask : GLbitfield {
                Color   = GL_COLOR_BUFFER_BIT,
                Depth   = GL_DEPTH_BUFFER_BIT,
                Stencil = GL_STENCIL_BUFFER_BIT,
                Color_Depth   = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                Color_Stencil = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                Depth_Stencil = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                Color_Depth_Stencil = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
            };

        public:
            Context();

            void makeActive(Util::Window* window);
            void bindWindow(Util::Window* window);


            void clearBuffers(Context::BufferMask mask);
            

            void setClearColor(const glm::vec4& data);
            void setClearDepth(const GLclampf value);
            void setClearStencil(const GLint value);
            

            const glm::vec4& getClearColor() const;
            GLclampf getClearDepth() const;
            GLint getClearStencil() const;

        private:
            void setActive(bool flag);
            bool isActive() const;

            bool _isActive;

            glm::vec4 _clearColor;
            GLclampf _clearDepth;
            GLint _clearStencil;

            Util::Window* _window;
    };

}

#endif