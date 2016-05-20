#pragma once

#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Shape.h>

#include <array>


namespace GLUL {

    namespace G2D {

        class GLUL_API Quad : public Shape {
            public:
                Quad();
                Quad(const Point& point1, const Point& point2, const Point& point3, const Point& point4);
                Quad(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3, const glm::vec2& position4);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::array<Point, 4> points;

            protected:
                void _pushToBatch(GeometryBatch& geometryBatch) const;
        };

    }

}
