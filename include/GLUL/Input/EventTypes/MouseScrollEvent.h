#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Event.h>

namespace GLUL {

    namespace Input {

        class GLUL_API MouseScrollEvent : public Event {
            public:
                MouseScrollEvent();
                MouseScrollEvent(ScrollDirection scrollDirection);

                ScrollDirection getDirection() const;

                void setDirection(ScrollDirection scrollDirection);

            public:
                MouseScrollEvent* asMouseScrollEvent();
                const MouseScrollEvent* asMouseScrollEvent() const;
                
            private:
                void _abstract() { }

                ScrollDirection _direction;
        };

    }

}
