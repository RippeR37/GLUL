#include <Utils/Interfaces/State.h>

namespace Util {

    namespace Interface {

        State::State() {
            _next = this;
        }

        State::~State() {
            _next = nullptr;
        }

        void State::handleInput() {
            if(shouldSkip())
                return;
        }

        State* State::getNext() {
            return _next;
        }

        void State::changeTo(State* nextState) {
            _next = nextState;
        }
    
        bool State::shouldSkip() {
            return (getNext() != this);
        }

        const State* const State::Quit = nullptr;

    }

}