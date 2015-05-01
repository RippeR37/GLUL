#include <Utils/Input/EventTypes/MouseScrollEvent.h>

namespace Util {

    namespace Input {

        MouseScrollEvent::MouseScrollEvent() : Event(Type::MouseScroll) {

        }

        MouseScrollEvent* MouseScrollEvent::asMouseScrollEvent() {
            return this;
        }

        const MouseScrollEvent* MouseScrollEvent::asMouseScrollEvent() const {
            return this;
        }

    }

}