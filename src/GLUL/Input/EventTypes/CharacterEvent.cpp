#include <GLUL/Input/EventTypes/CharacterEvent.h>


namespace GLUL {

    namespace Input {

        CharacterEvent::CharacterEvent() : CharacterEvent(0u) {

        }

        CharacterEvent::CharacterEvent(unsigned int code) : Event(Type::Character) {
            setCharacter(code);
        }

        unsigned int CharacterEvent::getCharacter() const {
            return _code;
        }

        void CharacterEvent::setCharacter(unsigned int code) {
            _code = code;
        }

        bool CharacterEvent::isASCII() const {
            return (_code < 256);
        }

        unsigned char CharacterEvent::asASCII() const {
            return static_cast<unsigned char>(_code);
        }


        CharacterEvent* CharacterEvent::asCharacterEvent() {
            return this;
        }

        const CharacterEvent* CharacterEvent::asCharacterEvent() const {
            return this;
        }

    }

}
