#ifndef UTILS_INPUT_EVENTTYPES_MOUSEMOVEMENTEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSEMOVEMENTEVENT_H_INCLUDED

#include <Utils/Input/Event.h>

#include <glm/vec2.hpp>

namespace Util {

    namespace Input {

        class MouseMovementEvent : public Event {
            public:
                MouseMovementEvent();
                MouseMovementEvent(float x, float y);
                MouseMovementEvent(const glm::vec2 position);

                float getX() const;
                float getY() const;
                const glm::vec2& getPosition() const;

                void setX(float x);
                void setY(float y);
                void setPosition(const glm::vec2& position);

            public:
                MouseMovementEvent* asMouseMovementEvent();
                const MouseMovementEvent* asMouseMovementEvent() const;
                
            private:
                void _abstract() { } 

                glm::vec2 _position;
        };

    }

}

#endif
