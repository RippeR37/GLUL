#ifndef UTILS_INPUT_EVENT_H_INCLUDED
#define UTILS_INPUT_EVENT_H_INCLUDED

#include <Utils/Config.h>


namespace Util {

    namespace Input {

        class KeyEvent;
        class MouseButtonEvent;
        class MouseMovementEvent;
        class MouseScrollEvent;

        class UTILS_API Event {
            public:
                enum class Type {
                    Key,
                    MouseButton,
                    MouseMovement,
                    MouseScroll,
                };

            public:
                Event(Type type);

                Type getType() const;

            public:
                Event* asEvent();
                const Event* asEvent() const;

                virtual KeyEvent* asKeyEvent();
                virtual MouseButtonEvent* asMouseButtonEvent();
                virtual MouseMovementEvent* asMouseMovementEvent();
                virtual MouseScrollEvent* asMouseScrollEvent();

                virtual const KeyEvent* asKeyEvent() const;
                virtual const MouseButtonEvent* asMouseButtonEvent() const;
                virtual const MouseMovementEvent* asMouseMovementEvent() const;
                virtual const MouseScrollEvent* asMouseScrollEvent() const;
            
            private:
                virtual void _abstract() = 0;

                Type _type;
        };

    }

}

#include <Utils/Input/EventTypes/KeyEvent.h>
#include <Utils/Input/EventTypes/MouseButtonEvent.h>
#include <Utils/Input/EventTypes/MouseMovementEvent.h>
#include <Utils/Input/EventTypes/MouseScrollEvent.h>

#endif
