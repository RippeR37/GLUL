#ifndef UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED

#include <Utils/Input/Event.h>
#include <Utils/Input/Types.h>

namespace Util {

    namespace Input {

        class MouseButtonEvent : public Event {
            public:
                MouseButtonEvent();
                MouseButtonEvent(MouseButton button, Action action);

                MouseButton getMouseButton() const;
                Action getAction() const;

                void setMouseButton(MouseButton button);
                void setAction(Action action);

            public:
                MouseButtonEvent* asMouseButtonEvent();
                const MouseButtonEvent* asMouseButtonEvent() const;
                
            private:
                void _abstract() { } 
                
                MouseButton _button;
                Action _action;
        };

    }

}

#endif
