#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>
#include <GLUL/Input/Types.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API MouseRelease : public EventTemplate<MouseRelease> {
                public:
                    MouseRelease(const GLUL::Input::MouseButton& button, const glm::vec2& position);
                    MouseRelease& operator=(const MouseRelease&) = delete;

                    const GLUL::Input::MouseButton button;
                    const glm::vec2 position;
            };

        }

    }

}
