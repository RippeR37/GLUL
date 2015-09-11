#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API MouseLeave : public EventTemplate<MouseLeave> {
                public:
                    MouseLeave();
                    MouseLeave& operator=(const MouseLeave&) = delete;
            };

        }

    }

}
