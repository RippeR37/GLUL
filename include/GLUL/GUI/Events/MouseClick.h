#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>
#include <GLUL/Input/Types.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API MouseClick : public EventTemplate<MouseClick> {
                public:
                    MouseClick(const GLUL::Input::MouseButton& button, const glm::vec2& position);
                    MouseClick& operator=(const MouseClick&) = delete;

                    const GLUL::Input::MouseButton button;
                    const glm::vec2 position;
            };

        }

    }

}
