#include <GLUL/Input/Event.h>


namespace GLUL {

    namespace Input {

        Event::Event(Type type) {
            _type = type;
        }


        Event::Type Event::getType() const {
            return _type;
        }


        Event* Event::asEvent() {
            return static_cast<Event*>(this);
        }

        const Event* Event::asEvent() const {
            return static_cast<const Event*>(this);
        }


        
        CharacterEvent* Event::asCharacterEvent() {
            return nullptr;
        }

        KeyEvent* Event::asKeyEvent() {
            return nullptr;
        }

        MouseButtonEvent* Event::asMouseButtonEvent() {
            return nullptr;
        }

        MouseMovementEvent* Event::asMouseMovementEvent() {
            return nullptr;
        }

        MouseScrollEvent* Event::asMouseScrollEvent() {
            return nullptr;
        }

        const CharacterEvent* Event::asCharacterEvent() const {
            return nullptr;
        }

        const KeyEvent* Event::asKeyEvent() const {
            return nullptr;
        }

        const MouseButtonEvent* Event::asMouseButtonEvent() const {
            return nullptr;
        }

        const MouseMovementEvent* Event::asMouseMovementEvent() const {
            return nullptr;
        }

        const MouseScrollEvent* Event::asMouseScrollEvent() const {
            return nullptr;
        }
        
    }

}
