#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Checkbox.h>


namespace GLUL {

    namespace GUI {

        Checkbox::Checkbox(const Container& parent, bool state)
            : Checkbox(parent, {}, {}, state) { }

        Checkbox::Checkbox(const Container& parent, const glm::vec2& size, const glm::vec2& position, bool state)
            : Component(parent, size, position), _state(state)
        {
            _initializeHandlers();
        }

        Checkbox::operator bool() const {
            return getState();
        }

        bool Checkbox::getState() const {
            return _state;
        }

        void Checkbox::setState(bool state) {
            if(getState() != state) {
                _state = state;
                setInvalid();

                onValueChange.call(*this, { !state, state });
            }
        }

        bool Checkbox::switchState() {
            setState(!getState());

            return getState();
        }

        void Checkbox::_initializeHandlers() {
            onMouseClick += Event::MouseClick::Handler(
                "__GLUL::GUI::Checkbox::MouseClick",
                [&](Component& component, const Event::MouseClick& onMouseClickEvent) {
                    Checkbox& checkbox = static_cast<Checkbox&>(component);

                    if(onMouseClickEvent.button == Input::MouseButton::Left)
                        checkbox.switchState();
                }
            );
        }

        void Checkbox::_pushToBatch(G2D::TexturedBatch& texBatch) const {
            (void) texBatch;

            // TODO: implement this
        }

    }

}
