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
                Quad(const Point& bottomLeftPoint, float size);
                Quad(const Point& bottomLeftPoint, const glm::vec2& size);
                Quad(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3, const glm::vec2& position4);
                Quad(const glm::vec2& bottomLeftPosition, float size);
                Quad(const glm::vec2& bottomLeftPosition, const glm::vec2& size);

                void setSquare(const Point& bottomLeftPoint, float size);
                void setRectangle(const Point& bottomLeftPoint, const glm::vec2& size);

                void setColor(const glm::vec4& color);
                const glm::vec4& getColor() const;

                std::array<Point, 4> points;

            protected:
                void _pushToBatch(Batch& batch) const;

                using Primitive::setColor;
        };

    }

}
