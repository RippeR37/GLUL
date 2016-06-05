#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/TextField.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            TextField::TextField(const Container& parent, const std::string& value)
                : TextField(parent, {}, {}, value) { }

            TextField::TextField(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value)
                : Component(parent, size, position), _value(value)
            {
                _initializeHandlers();
            }

            const std::string& TextField::getValue() const {
                return _value;
            }

            void TextField::setValue(const std::string& value) {
                if(_value != value) {
                    auto oldValue = getValue();
                    _value = value;

                    setInvalid();
                    onValueChange.call(*this, { oldValue, getValue() });
                }
            }

            void TextField::_initializeHandlers() {
                onKeyStroke += Event::KeyStroke::Handler(
                    "__GLUL::GUI::Base::TextField::KeyStroke",
                    [&](Component& component, const Event::KeyStroke& onKeyStrokeEvent) {
                        TextField& textField = static_cast<TextField&>(component);

                        switch(onKeyStrokeEvent.key) {
                            case GLUL::Input::Key::Backspace:
                                if(textField.getValue().length() > 0)
                                    textField.setValue(textField.getValue().substr(0, textField.getValue().length() - 1));
                                break;

                            default:
                                break;
                        }
                    }
                );

                onTextInput += Event::TextInput::Handler(
                    "__GLUL::GUI::Base::TextField::TextInput",
                    [&](Component& component, const Event::TextInput& onTextInputEvent) {
                        TextField& textField = static_cast<TextField&>(component);

                        textField.setValue(textField.getValue() + onTextInputEvent.text);
                    }
                );
            }

        }

    }

}
