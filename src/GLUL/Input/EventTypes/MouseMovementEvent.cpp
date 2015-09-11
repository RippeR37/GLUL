#include <GLUL/Input/EventTypes/MouseMovementEvent.h>


namespace GLUL {

    namespace Input {

        MouseMovementEvent::MouseMovementEvent() : Event(Type::MouseMovement) {
            setPosition(glm::vec2(0.0f));
        }

        MouseMovementEvent::MouseMovementEvent(float x, float y) : Event(Type::MouseMovement)  {
            setPosition(glm::vec2(x, y));
        }

        MouseMovementEvent::MouseMovementEvent(const glm::vec2& position) : Event(Type::MouseMovement) {
            setPosition(position);
        }

        float MouseMovementEvent::getX() const {
            return _position.x;
        }

        float MouseMovementEvent::getY() const {
            return _position.y;
        }

        const glm::vec2& MouseMovementEvent::getPosition() const {
            return _position;
        }

        void MouseMovementEvent::setX(float x) {
            _position.x = x;
        }

        void MouseMovementEvent::setY(float y) {
            _position.y = y;
        }

        void MouseMovementEvent::setPosition(const glm::vec2& position) {
            _position = position;
        }


        MouseMovementEvent* MouseMovementEvent::asMouseMovementEvent() {
            return this;
        }

        const MouseMovementEvent* MouseMovementEvent::asMouseMovementEvent() const {
            return this;
        }

    }

}
