#include <Utils/GL+/GUI/Event.h>

namespace GL {

    namespace GUI {

        Event::Event(Type type) {
            setType(type);
        }

        void Event::setKey(Key key) {
            _key = key;
        }
                
        void Event::setType(Type type) {
            _type = type;
        }

        void Event::setPosition(const glm::vec2& position) {
            _position = position;
        }

        Event::Key Event::getKey() const {
            return _key;
        }
                
        Event::Type Event::getType() const {
            return _type;
        }

        const glm::vec2& Event::getPosition() const {
            return _position;
        }

    }

}