#include <Utils/Input/EventTypes/MouseButtonEvent.h>

namespace Util {

    namespace Input {

        MouseButtonEvent::MouseButtonEvent() : Event(Type::MouseButton) {

        }

        MouseButtonEvent* MouseButtonEvent::asMouseButtonEvent() {
            return this;
        }

        const MouseButtonEvent* MouseButtonEvent::asMouseButtonEvent() const {
            return this;
        }

    }

}