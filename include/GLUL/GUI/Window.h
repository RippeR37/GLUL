#pragma once

#include <GLUL/GUI/Container.h>
#include <GLUL/Input/EventHandler.h>
#include <GLUL/Window.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API Window : public GLUL::Window, public Container, protected GLUL::Input::EventHandler {
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
                virtual void handleInputEvent(const GLUL::Input::Event& inputEvent);

                using Container::update;
        };

    }

}
