#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Ring : public Shape {
            public:
                Ring();
                Ring(const Point& center, float innerRadius, float outerRadius);
                Ring(const glm::vec2& center, float innerRadius, float outerRadius);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                Point center;
                float innerRadius;
                float outerRadius;
                unsigned int pointCount;

                static unsigned int defaultPointCount(float outerRadius);

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;

                using Primitive::setColor;
        };

    }

}
