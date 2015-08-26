#ifndef UTILS_INPUT_EVENTTYPES_MOUSESCROLLEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSESCROLLEVENT_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Input/Event.h>

namespace Util {

    namespace Input {

        class UTILS_API MouseScrollEvent : public Event {
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

#endif
