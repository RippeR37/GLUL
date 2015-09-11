#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API MouseMove : public EventTemplate<MouseMove> {
                public:
                    MouseMove(const glm::vec2& position);
                    MouseMove& operator=(const MouseMove&) = delete;

                    const glm::vec2 position;
            };

        }

    }

}
