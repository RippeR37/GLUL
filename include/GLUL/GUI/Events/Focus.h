#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API Focus : public EventTemplate<Focus> {
                public:
                    Focus& operator=(const Focus&) = delete;
            };

        }

    }

}
