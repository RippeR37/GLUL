#ifndef UTILS_GL_GUI_EVENTS_MOUSEMOVE_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_MOUSEMOVE_H_INCLUDED

#include <Utils/GL+/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>

namespace GL {

    namespace GUI {

        namespace Event {

            class MouseMove : public EventTemplate<MouseMove> {
                public:
                    MouseMove(const glm::vec2& position) : position(position) { }

                    MouseMove& operator=(const MouseMove&) = delete;

                    const glm::vec2 position;
            };

        }

    }

}

#endif