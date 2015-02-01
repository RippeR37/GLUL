#ifndef UTILS_GL_GUI_WINDOW_H_INCLUDED
#define UTILS_GL_GUI_WINDOW_H_INCLUDED

#include <Utils/GL+/GUI/Container.h>
#include <Utils/Window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace GL {

    namespace GUI {

        class Window : public Container, public Util::Window {
            public:
                Window();
                virtual ~Window();
            
                virtual void update();
                
                void setSize(unsigned int width, unsigned int height);
                void setSize(const glm::vec2& size);
                void setSize(const glm::uvec2& size);

            protected:

        };

    }

}


#endif