#include <GLUL/Interfaces/State.h>

namespace GLUL {

    namespace Interface {

        State::State() {
            _next = this;
        }

        State::~State() {
            _next = nullptr;
        }

        void State::handleInputEvent(const Input::Event& inputEvent) {
            if(shouldSkip())
                return;

            (void) inputEvent;
        }

        State* State::getNext() {
            return _next;
        }

        void State::_update(const double frameTime) {
            if(!shouldSkip())
                update(frameTime);
        }

        void State::_render() {
            if(!shouldSkip())
                render();
        }

        void State::_onLoad() {
            changeTo(this);
            onLoad();
        }

        void State::_onUnload() {
            onUnload();
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