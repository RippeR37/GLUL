#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/TextField.h>

#include <cctype>


namespace GLUL {

    namespace GUI {

        namespace Base {

            TextField::TextField(const Container& parent, const std::string& value)
                : TextComponent(parent, value) { }

            TextField::TextField(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value)
                : TextComponent(parent, size, position, value) { }

            bool TextField::_isAcceptedCharacter(char character) {
                return std::isprint(character) != 0;
            }

        }

    }

}
