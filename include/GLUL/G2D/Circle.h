#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Circle : public Shape {
            public:
                Circle();
                Circle(const Point& center, float radius);
                Circle(const glm::vec2& center, float radius);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                Point center;
                float radius;
                unsigned int pointCount;

                static unsigned int defaultPointCount(float radius);

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                using Primitive::setColor;
        };

    }

}
