#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API TextComponent : public Component {
                public:
                    virtual ~TextComponent() = default;

                    virtual const std::string& getValue() const;

                    virtual void setValue(const std::string& value);

                    Event::HandlerAggregator<Event::ValueChange<std::string>> onValueChange;

                protected:
                    TextComponent(const Container& parent, const std::string& value);
                    TextComponent(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value);

                    void _initializeHandlers();
                    virtual std::string _getValidatedText(const std::string& text);
                    virtual bool _isAcceptedCharacter(char character) = 0;

                    std::string _value;

                    friend class Container;
            };

        }

    }

}
