#include <Utils/Input/EventTypes/MouseButtonEvent.h>

namespace Util {

    namespace Input {

        MouseButtonEvent::MouseButtonEvent() : Event(Type::MouseButton) {

        }

        MouseButtonEvent::MouseButtonEvent(MouseButton button, Action action) : Event(Type::MouseButton) {
            setMouseButton(button);
            setAction(action);
        }


        MouseButton MouseButtonEvent::getMouseButton() const {
            return _button;
        }

        Action MouseButtonEvent::getAction() const {
            return _action;
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