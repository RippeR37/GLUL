#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API ValueChange : public EventTemplate<ValueChange> {
                public:
                    ValueChange();
                    ValueChange& operator=(const ValueChange&) = delete;
            };

        }

    }

}
