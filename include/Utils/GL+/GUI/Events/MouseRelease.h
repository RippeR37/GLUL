#ifndef UTILS_GL_GUI_EVENTS_MOUSERELEASE_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_MOUSERELEASE_H_INCLUDED

#include <Utils/GL+/GUI/Events/EventTemplate.hpp>
#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>


namespace GL {

    namespace GUI {

        namespace Event {

            class UTILS_API MouseRelease : public EventTemplate<MouseRelease> {
                public:
                    MouseRelease(const Util::Input::MouseButton& button, const glm::vec2& position);
                    MouseRelease& operator=(const MouseRelease&) = delete;

                    const Util::Input::MouseButton button;
                    const glm::vec2 position;
            };

        }

    }

}

#endif
