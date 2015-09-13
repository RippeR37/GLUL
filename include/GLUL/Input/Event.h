#pragma once

#include <GLUL/Config.h>


namespace GLUL {

    namespace Input {

        class CharacterEvent;
        class KeyEvent;
        class MouseButtonEvent;
        class MouseMovementEvent;
        class MouseScrollEvent;

        class GLUL_API Event {
            public:
                enum class Type {
                    Character,
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
                
                virtual CharacterEvent* asCharacterEvent();
                virtual KeyEvent* asKeyEvent();
                virtual MouseButtonEvent* asMouseButtonEvent();
                virtual MouseMovementEvent* asMouseMovementEvent();
                virtual MouseScrollEvent* asMouseScrollEvent();
                
                virtual const CharacterEvent* asCharacterEvent() const;
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

#include <GLUL/Input/EventTypes/CharacterEvent.h>
#include <GLUL/Input/EventTypes/KeyEvent.h>
#include <GLUL/Input/EventTypes/MouseButtonEvent.h>
#include <GLUL/Input/EventTypes/MouseMovementEvent.h>
#include <GLUL/Input/EventTypes/MouseScrollEvent.h>
