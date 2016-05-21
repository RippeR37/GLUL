#pragma once

#include <GLUL/G2D/TexturedPoint.h>
#include <GLUL/G2D/TexturedShape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API TexturedTriangle : public TexturedShape {
            public:
                TexturedTriangle();
                TexturedTriangle(const TexturedPoint& point1, const TexturedPoint& point2, const TexturedPoint& point3);

                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::array<TexturedPoint, 3> points;

            protected:
                void _pushToBatch(TexturedGeometryBatch& texGeometryBatch, const GL::Texture& texture) const;

                using TexturedPrimitive::setColor;
        };

    }

}
