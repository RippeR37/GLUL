#ifndef UTILS_GL_GUI_EVENT_H_INCLUDED
#define UTILS_GL_GUI_EVENT_H_INCLUDED

#include <glm/vec2.hpp>

namespace GL {

    namespace GUI {

        class Event {
            public:
                enum class Type : int {
                    MouseClick = 0,
                    MouseHoverEnter = 1,
                    MouseHoverLeave = 2,
                    MouseButtonPress = 3,
                    MouseButtonRelease = 4,
                    KeyPress = 5,
                    KeyReleas = 6,
                };
                
                typedef int Key;

            public:
                Event(Type type);
                
                void setKey(Key key);
                void setType(Type type);
                void setPosition(const glm::vec2& position);
                
                Key  getKey() const;
                Type getType() const;
                const glm::vec2& getPosition() const;

            private:
                Key _key;
                Type _type;
                glm::vec2 _position;
        };

    }

}


#endif