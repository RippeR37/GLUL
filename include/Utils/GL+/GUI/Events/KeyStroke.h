#ifndef UTILS_GL_GUI_EVENTS_KEYSTROKE_H_INCLUDED
#define UTILS_GL_GUI_EVENTS_KEYSTROKE_H_INCLUDED

#include <Utils/GL+/GUI/Events/EventTemplate.hpp>
#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>


namespace GL {

    namespace GUI {

        namespace Event {

            class UTILS_API KeyStroke : public EventTemplate<KeyStroke> {
                public:
                    KeyStroke(const Util::Input::Key& key);
                    KeyStroke& operator=(const KeyStroke&) = delete;

                    const Util::Input::Key key;
            };

        }

    }

}

#endif
