#ifndef UTILS_GL_GUI_EVENTS_MOUSEENTER_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_MOUSEENTER_H_INCLUDED

#include <Utils/GL+/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>

namespace GL {

    namespace GUI {

        namespace Event {

            class MouseEnter : public EventTemplate<MouseEnter> {
                public:
                    MouseEnter(const glm::vec2& position) : position(position) { }

                    MouseEnter& operator=(const MouseEnter&) = delete;

                    const glm::vec2 position;
            };

        }

    }

}

#endif