#pragma once

#include <GLUL/GUI/Base/TextComponent.h>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API TextArea : public TextComponent {
                public:
                    virtual ~TextArea() = default;

                protected:
                    TextArea(const Container& parent, const std::string& value);
                    TextArea(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value);

                    virtual bool _isAcceptedCharacter(char character);

                    friend class Container;
            };

        }

    }

}
