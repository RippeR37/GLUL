#ifndef UTILS_GL_GUI_EVENTS_ONCLICK_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_ONCLICK_H_INCLUDED

#include <Utils/GL+/GUI/Component.h>
#include <Utils/GL+/GUI/Events/EventTemplate.h>
#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>

#include <string>
#include <functional>

namespace GL {

    namespace GUI {

        namespace Event {

            class OnClick : public EventTemplate<OnClick> {
                public:
                    OnClick(const Util::Input::MouseButton& button, const glm::vec2& position) : button(button), position(position) { }

                    OnClick& operator=(const OnClick&) = delete;

                    const Util::Input::MouseButton button;
                    const glm::vec2 position;
            };

        }

    }

}

#endif