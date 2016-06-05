#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/TextComponent.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            TextComponent::TextComponent(const Container& parent, const std::string& value)
                : TextComponent(parent, {}, {}, value) { }

            TextComponent::TextComponent(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value)
                : Component(parent, size, position), _value(value)
            {
                _initializeHandlers();
            }

            const std::string& TextComponent::getValue() const {
                return _value;
            }

            void TextComponent::setValue(const std::string& value) {
                if(_value != value) {
                    auto oldValue = getValue();
                    _value = value;

                    setInvalid();
                    onValueChange.call(*this, { oldValue, getValue() });
                }
            }

            void TextComponent::_initializeHandlers() {
                onKeyStroke += Event::KeyStroke::Handler(
                    "__GLUL::GUI::Base::TextComponent::KeyStroke",
                    [&](Component& component, const Event::KeyStroke& onKeyStrokeEvent) {
                        TextComponent& textComponent = static_cast<TextComponent&>(component);

                        switch(onKeyStrokeEvent.key) {
                            case GLUL::Input::Key::Backspace:
                                if(textComponent.getValue().length() > 0)
                                    textComponent.setValue(textComponent.getValue().substr(0, textComponent.getValue().length() - 1));
                                break;

                            default:
                                break;
                        }
                    }
                );

                onTextInput += Event::TextInput::Handler(
                    "__GLUL::GUI::Base::TextComponent::TextInput",
                    [&](Component& component, const Event::TextInput& onTextInputEvent) {
                        TextComponent& textComponent = static_cast<TextComponent&>(component);
                        auto validatedText = textComponent._getValidatedText(onTextInputEvent.text);

                        textComponent.setValue(textComponent.getValue() + validatedText);
                    }
                );
            }

            std::string TextComponent::_getValidatedText(const std::string& text) {
                std::string result;

                for(auto character : text)
                    if(_isAcceptedCharacter(character))
                        result.push_back(character);

                return result;
            }

        }

    }

}
