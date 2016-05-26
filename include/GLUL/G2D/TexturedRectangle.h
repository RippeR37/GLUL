#pragma once

#include <GLUL/G2D/TexturedPoint.h>
#include <GLUL/G2D/TexturedShape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API TexturedRectangle : public TexturedShape {
            public:
                TexturedRectangle();
                TexturedRectangle(const glm::vec2& position, float size);
                TexturedRectangle(const glm::vec2& position, float size, const glm::vec2& texPosition, float texSize);
                TexturedRectangle(const glm::vec2& position, const glm::vec2& size);
                TexturedRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec2& texPosition, const glm::vec2& texSize);
                explicit TexturedRectangle(const TexturedPoint& point, float size, float texSize);
                explicit TexturedRectangle(const TexturedPoint& point, const glm::vec2& size, const glm::vec2& texSize);


                void setPosition(const glm::vec2& position);
                const glm::vec2& getPosition() const;

                void setSize(float size);
                void setSize(const glm::vec2& size);
                const glm::vec2& getSize() const;

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                void setTexPosition(const glm::vec2& texPosition);
                const glm::vec2& getTexPosition() const;

                void setTexSize(float texSize);
                void setTexSize(const glm::vec2& texSize);
                const glm::vec2& getTexSize() const;

            protected:
                void _pushToBatch(TexturedBatch& texBatch, const GL::Texture& texture) const;

                glm::vec2 _position;
                glm::vec2 _size;
                glm::vec4 _color;
                glm::vec2 _texPos;
                glm::vec2 _texSize;
        };

    }

}
