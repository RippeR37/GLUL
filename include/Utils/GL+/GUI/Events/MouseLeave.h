#ifndef UTILS_GL_GUI_EVENTS_MOUSELEAVE_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_MOUSELEAVE_H_INCLUDED

#include <Utils/GL+/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GL {

    namespace GUI {

        namespace Event {

            class UTILS_API MouseLeave : public EventTemplate<MouseLeave> {
                public:
                    MouseLeave();
                    MouseLeave& operator=(const MouseLeave&) = delete;
            };

        }

    }

}

#endif
