#ifndef UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED

#include <Utils/Input/Event.h>

namespace Util {

    namespace Input {

        class MouseButtonEvent : public Event {
            public:
                MouseButtonEvent();

                MouseButtonEvent* asMouseButtonEvent();
                const MouseButtonEvent* asMouseButtonEvent() const;
                
            private:
                void _abstract() { } 
        };

    }

}

#endif
