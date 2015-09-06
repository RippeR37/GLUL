#ifndef UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_MOUSEBUTTONEVENT_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Input/Event.h>
#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>


namespace Util {

    namespace Input {

        class UTILS_API MouseButtonEvent : public Event {
            public:
                MouseButtonEvent();
                MouseButtonEvent(MouseButton button, Action action, float x, float y);
                MouseButtonEvent(MouseButton button, Action action, const glm::vec2& position);

                float getX() const;
                float getY() const;
                const glm::vec2& getPosition() const;
                MouseButton getMouseButton() const;
                Action getAction() const;

                void setX(float x);
                void setY(float y);
                void setPosition(const glm::vec2& position);
                void setMouseButton(MouseButton button);
                void setAction(Action action);

            public:
                MouseButtonEvent* asMouseButtonEvent();
                const MouseButtonEvent* asMouseButtonEvent() const;
                
            private:
                void _abstract() { } 
                
                MouseButton _button;
                Action _action;
                glm::vec2 _position;
        };

    }

}

#endif
