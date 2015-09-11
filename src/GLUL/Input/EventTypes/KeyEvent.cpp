#include <GLUL/Input/EventTypes/KeyEvent.h>


namespace GLUL {

    namespace Input {

        KeyEvent::KeyEvent() : Event(Type::Key) {

        }
        
        KeyEvent::KeyEvent(Key key, Action action) : Event(Type::Key) {
            setKey(key);
            setAction(action);
        }

        Key KeyEvent::getKey() const {
            return _key;
        }

        Action KeyEvent::getAction() const {
            return _action;
        }

        void KeyEvent::setKey(Key key) {
            _key = key;
        }

        void KeyEvent::setAction(Action action) {
            _action = action;
        }


        KeyEvent* KeyEvent::asKeyEvent() {
            return this;
        }

        const KeyEvent* KeyEvent::asKeyEvent() const {
            return this;
        }

    }

}
