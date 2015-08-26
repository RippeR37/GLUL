#ifndef UTILS_INPUT_EVENTTYPES_KEYEVENT_H_INCLUDED
#define UTILS_INPUT_EVENTTYPES_KEYEVENT_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Input/Event.h>
#include <Utils/Input/Types.h>


namespace Util {

    namespace Input {

        class UTILS_API KeyEvent : public Event {
            public:
                KeyEvent();
                KeyEvent(Key key, Action action);

                Key getKey() const;
                Action getAction() const;

                void setKey(Key key);
                void setAction(Action action);

            public:
                KeyEvent* asKeyEvent();
                const KeyEvent* asKeyEvent() const;
                
            private:
                void _abstract() { }

                Key _key;
                Action _action;
        };

    }

}

#endif
