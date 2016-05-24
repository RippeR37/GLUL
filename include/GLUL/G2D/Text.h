#pragma once

#include <GLUL/G2D/Font.h>
#include <GLUL/G2D/HorizontalAlignment.h>
#include <GLUL/G2D/TexturedShape.h>

#include <functional>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API Text {
            public:
                using Alignment = HorizontalAlignment;

            public:
                Text();
                Text(const std::string& text);
                Text(const std::string& text, const glm::vec2& position);
                Text(const std::string& text, const glm::vec2& position, Alignment alignment);
                Text(const std::string& text, const glm::vec2& position, const glm::vec3& color);
                Text(const std::string& text, const glm::vec2& position, const glm::vec3& color, Alignment alignment);
                Text(const std::string& text, const glm::vec2& position, const glm::vec4& color);
                Text(const std::string& text, const glm::vec2& position, const glm::vec4& color, Alignment alignment);

                Text& operator=(const std::string& text);

                operator const std::string&() const;

                void render(const Font& font) const;
                void render(const GL::Program& program, const Font& font) const;

                void setText(const std::string& text);
                const std::string& getText() const;

                void setPosition(const glm::vec2& position);
                const glm::vec2& getPosition() const;

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                void setAlignment(Alignment alignment);
                Alignment getAlignment() const;

            protected:
                void _moveCursor(glm::vec2& cursorPosition, char character, const Font& font) const;
                void _pushToBatch(TexturedGeometryBatch& texGeometryBatch, const Font& font) const;

                std::string _text;
                glm::vec2 _position;
                glm::vec4 _color;
                Alignment _alignment;

                friend class TexturedGeometryBatch;
        };

    }

}
