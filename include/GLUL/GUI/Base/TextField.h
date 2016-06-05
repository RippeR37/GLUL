#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        class GLUL_API TextField : public Component {
            public:
                const std::string& getValue() const;

                void setValue(const std::string& value);

                Event::HandlerAggregator<Event::ValueChange<std::string>> onValueChange;

            protected:
                TextField(const Container& parent, const std::string& value = "");
                TextField(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& value = "");

                void _initializeHandlers();
                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                std::string _value;

                friend class Container;
        };

    }

}
