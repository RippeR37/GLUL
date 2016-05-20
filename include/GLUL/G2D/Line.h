#pragma once

#include <GLUL/G2D/Primitive.h>
#include <GLUL/G2D/Point.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Line : public Primitive {
            public:
                Line(unsigned int thickness = 1u);
                Line(const Point& point1, const Point& point2, unsigned int thickness = 1u);
                Line(const glm::vec2& position1, const glm::vec2& position2, unsigned int thickness = 1u);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                void setThickness(unsigned int thickness);

                std::array<Point, 2> points;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;
        };

    }

}
