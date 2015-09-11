#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Event.h>
#include <GLUL/Input/Types.h>


namespace GLUL {

    namespace Input {

        class GLUL_API KeyEvent : public Event {
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
