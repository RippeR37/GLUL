#ifndef UTILS_GL_GUI_WINDOW_H_INCLUDED
#define UTILS_GL_GUI_WINDOW_H_INCLUDED

#include <Utils/Input/EventHandler.h>
#include <Utils/GL+/GUI/Container.h>
#include <Utils/Window.h>

#include <glm/vec2.hpp>

namespace GL {

    namespace GUI {

        class Window : public Util::Window, public Container, protected Util::Input::EventHandler {
            public:
                Window();
                Window(unsigned int width, unsigned int height, const std::string& title);
                Window(const glm::uvec2& size, const std::string& title);
                virtual ~Window();
            
                virtual void update();
                
                void setSize(unsigned int width, unsigned int height);
                void setSize(const glm::vec2& size);
                void setSize(const glm::uvec2& size);

            protected:
                virtual void handleInputEvent(const Util::Input::Event& inputEvent);

        };

    }

}


#endif