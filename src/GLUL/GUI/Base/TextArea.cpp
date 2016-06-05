#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/TextArea.h>

#include <cctype>


namespace GLUL {

    namespace GUI {

        namespace Base {

            TextArea::TextArea(const Container& parent, const std::string& value)
                : TextComponent(parent, value) { }

            TextArea::TextArea(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value)
                : TextComponent(parent, size, position, value) { }

            bool TextArea::_isAcceptedCharacter(char character) {
                return (std::isprint(character) != 0) || (character == '\t') || (character == '\n');
            }

        }

    }

}
