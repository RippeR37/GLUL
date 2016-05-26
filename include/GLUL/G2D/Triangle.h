#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Triangle : public Shape {
            public:
                Triangle();
                Triangle(const Point& point1, const Point& point2, const Point& point3);
                Triangle(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::array<Point, 3> points;

            protected:
                void _pushToBatch(Batch& batch) const;

                using Primitive::setColor;
        };

    }

}
