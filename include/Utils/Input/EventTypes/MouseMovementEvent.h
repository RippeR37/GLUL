#ifndef UTILS_INPUT_EVENTTYPES_MOUSEMOVEMENTEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSEMOVEMENTEVENT_H_INCLUDED

#include <Utils/Input/Event.h>

namespace Util {

    namespace Input {

        class MouseMovementEvent : public Event {
            public:
                MouseMovementEvent();

                MouseMovementEvent* asMouseMovementEvent();
                const MouseMovementEvent* asMouseMovementEvent() const;
                
            private:
                void _abstract() { } 
        };

    }

}

#endif
