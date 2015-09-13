#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Event.h>
#include <GLUL/Input/Types.h>


namespace GLUL {

    namespace Input {

        class GLUL_API CharacterEvent : public Event {
            public:
                CharacterEvent();
                CharacterEvent(unsigned int code);

                unsigned int getCharacter() const;
                void setCharacter(unsigned int code);

                bool isASCII() const;
                unsigned char asASCII() const;

            public:
                CharacterEvent* asCharacterEvent();
                const CharacterEvent* asCharacterEvent() const;
                
            private:
                void _abstract() { }

                unsigned int _code;
        };

    }

}
