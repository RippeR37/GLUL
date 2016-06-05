#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/RadioButton.h>
#include <GLUL/GUI/Base/RadioButtonGroup.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            RadioButton::RadioButton(const Container& parent, RadioButtonGroup& group, bool state)
                : RadioButton(parent, group, {}, {}, state) { }

            RadioButton::RadioButton(const Container& parent, RadioButtonGroup& group,
                const glm::vec2& size, const glm::vec2& position, bool state)
                : Component(parent, size, position), _group(group), _state(state)
            {
                _initializeHandlers();
            }

            RadioButton::operator bool() const {
                return isSet();
            }

            bool RadioButton::isSet() const {
                return _state;
            }

            void RadioButton::set() {
                _group.set(*this);
            }

            void RadioButton::_initializeHandlers() {
                onMouseClick += Event::MouseClick::Handler(
                    "__GLUL::GUI::Base::RadioButton::MouseClick",
                    [](Component& component, const Event::MouseClick& onMouseClickEvent) {
                        RadioButton& radioButton = static_cast<RadioButton&>(component);

                        if(onMouseClickEvent.button == Input::MouseButton::Left)
                            radioButton._group.set(radioButton);
                    }
                );
            }

            void RadioButton::_setState(bool state) {
                if(isSet() != state) {
                    _state = state;
                    setInvalid();

                    onValueChange.call(*this, { !state, state });
                }
            }

        }

    }

}
