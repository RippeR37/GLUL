#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>
#include <GLUL/Input/Types.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API KeyStroke : public EventTemplate<KeyStroke> {
                public:
                    KeyStroke(const GLUL::Input::Key& key);
                    KeyStroke& operator=(const KeyStroke&) = delete;

                    const GLUL::Input::Key key;
            };

        }

    }

}
