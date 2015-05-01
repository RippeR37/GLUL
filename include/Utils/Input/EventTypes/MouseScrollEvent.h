#ifndef UTILS_INPUT_EVENTTYPES_MOUSESCROLLEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSESCROLLEVENT_H_INCLUDED

#include <Utils/Input/Event.h>

namespace Util {

    namespace Input {

        class MouseScrollEvent : public Event {
            public:
                MouseScrollEvent();

                MouseScrollEvent* asMouseScrollEvent();
                const MouseScrollEvent* asMouseScrollEvent() const;
                
            private:
                void _abstract() { } 
        };

    }

}

#endif
