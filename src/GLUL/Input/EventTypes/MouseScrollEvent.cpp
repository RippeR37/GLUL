#include <GLUL/Input/EventTypes/MouseScrollEvent.h>


namespace GLUL {

    namespace Input {

        MouseScrollEvent::MouseScrollEvent() : Event(Type::MouseScroll) {

        }
        
        MouseScrollEvent::MouseScrollEvent(ScrollDirection scrollDirection) : Event(Type::MouseScroll) {
            setDirection(scrollDirection);
        }


        ScrollDirection MouseScrollEvent::getDirection() const {
            return _direction;
        }

        void MouseScrollEvent::setDirection(ScrollDirection scrollDirection) {
            _direction = scrollDirection;
        }


        MouseScrollEvent* MouseScrollEvent::asMouseScrollEvent() {
            return this;
        }

        const MouseScrollEvent* MouseScrollEvent::asMouseScrollEvent() const {
            return this;
        }

    }

}
