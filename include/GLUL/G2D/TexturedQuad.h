#pragma once

#include <GLUL/G2D/TexturedPoint.h>
#include <GLUL/G2D/TexturedShape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API TexturedQuad : public TexturedShape {
            public:
                TexturedQuad();
                TexturedQuad(const TexturedPoint& point1, const TexturedPoint& point2,
                    const TexturedPoint& point3, const TexturedPoint& point4);
                TexturedQuad(const TexturedPoint& bottomLeftPoint, float size, float texSize);
                TexturedQuad(const TexturedPoint& bottomLeftPoint, const glm::vec2& size, const glm::vec2& texSize);

                void setSquare(const TexturedPoint& bottomLeftPoint, float size, float texSize);
                void setRectangle(const TexturedPoint& bottomLeftPoint, const glm::vec2& size, const glm::vec2& texSize);

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::array<TexturedPoint, 4> points;

            protected:
                void _pushToBatch(TexturedBatch& texBatch, const GL::Texture& texture) const;
        };

    }

}
