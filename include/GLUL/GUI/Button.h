#pragma once

#include <GLUL/GUI/Component.h>

#include <glm/vec2.hpp>

#include <string>


namespace GLUL {

    namespace GUI {

        class GLUL_API Button : public Component {
            public:
                const std::string& getText() const;

                void setText(const std::string& text);

            protected:
                Button(const Container& parent);
                Button(const Container& parent, const glm::vec2& size, const glm::vec2& position);
                Button(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& text);

                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                std::string _text;

                friend class Container;
        };

    }

}
