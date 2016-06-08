#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/Checkbox.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Checkbox::Checkbox(const Container& parent, bool state, Background* background)
                : Checkbox(parent, {}, {}, state, background) { }

            Checkbox::Checkbox(const Container& parent, const glm::vec2& size, const glm::vec2& position, bool state, Background* background)
                : ComponentWithBackground(parent, size, position, background), mark(*this), _state(state)
            {
                _initializeHandlers();
            }

            Checkbox::operator bool() const {
                return isSet();
            }

            bool Checkbox::isSet() const {
                return _state;
            }

            void Checkbox::set(bool state) {
                if(isSet() != state) {
                    _state = state;
                    setInvalid();

                    onValueChange.call(*this, { !state, state });
                }
            }

            bool Checkbox::switchState() {
                set(!isSet());

                return isSet();
            }

            void Checkbox::_initializeHandlers() {
                onMouseClick += Event::MouseClick::Handler(
                    "__GLUL::GUI::Base::Checkbox::MouseClick",
                    [&](Component& component, const Event::MouseClick& onMouseClickEvent) {
                        Checkbox& checkbox = static_cast<Checkbox&>(component);

                        if(onMouseClickEvent.button == Input::MouseButton::Left)
                            checkbox.switchState();
                    }
                );
            }

        }

    }

}
