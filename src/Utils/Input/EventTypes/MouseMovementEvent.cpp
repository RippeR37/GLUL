#include <Utils/Input/EventTypes/MouseMovementEvent.h>

namespace Util {

    namespace Input {

        MouseMovementEvent::MouseMovementEvent() : Event(Type::MouseMovement) {

        }

        MouseMovementEvent* MouseMovementEvent::asMouseMovementEvent() {
            return this;
        }

        const MouseMovementEvent* MouseMovementEvent::asMouseMovementEvent() const {
            return this;
        }

    }

}