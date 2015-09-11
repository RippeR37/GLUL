#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API MouseEnter : public EventTemplate<MouseEnter> {
                public:
                    MouseEnter(const glm::vec2& position);
                    MouseEnter& operator=(const MouseEnter&) = delete;

                    const glm::vec2 position;
            };

        }

    }

}
