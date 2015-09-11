#include <GLUL/Input/EventTypes/MouseButtonEvent.h>


namespace GLUL {

    namespace Input {

        MouseButtonEvent::MouseButtonEvent() : Event(Type::MouseButton) {

        }

        MouseButtonEvent::MouseButtonEvent(MouseButton button, Action action, float x, float y) : MouseButtonEvent(button, action, glm::vec2(x, y)) {

        }

        MouseButtonEvent::MouseButtonEvent(MouseButton button, Action action, const glm::vec2& position) : Event(Type::MouseButton) {
            setMouseButton(button);
            setAction(action);
            setPosition(position);
        }


        float MouseButtonEvent::getX() const {
            return getPosition().x;
        }

        float MouseButtonEvent::getY() const {
            return getPosition().y;
        }

        const glm::vec2& MouseButtonEvent::getPosition() const {
            return _position;
        }

        MouseButton MouseButtonEvent::getMouseButton() const {
            return _button;
        }

        Action MouseButtonEvent::getAction() const {
            return _action;
        }

        void MouseButtonEvent::setX(float x) {
            _position.x = x;
        }

        void MouseButtonEvent::setY(float y) {
            _position.y = y;
        }

        void MouseButtonEvent::setPosition(const glm::vec2& position) {
            _position = position;
        }

        void MouseButtonEvent::setMouseButton(MouseButton button) {
            _button = button;
        }

        void MouseButtonEvent::setAction(Action action) {
            _action = action;
        }


        MouseButtonEvent* MouseButtonEvent::asMouseButtonEvent() {
            return this;
        }

        const MouseButtonEvent* MouseButtonEvent::asMouseButtonEvent() const {
            return this;
        }

    }

}
