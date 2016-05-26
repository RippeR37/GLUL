#include <GLUL/G2D/Triangle.h>


namespace GLUL {

    namespace G2D {

        Triangle::Triangle() : points({}) { }

        Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) {
            points[0] = point1;
            points[1] = point2;
            points[2] = point3;
        }

        Triangle::Triangle(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3)
            : Triangle(Point(position1), Point(position2), Point(position3)) { }

        void Triangle::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& Triangle::getColor() const {
            return points[0].getColor();
        }

        void Triangle::_pushToBatch(Batch& batch) const {
            std::vector<glm::vec4> vertexData {
                glm::vec4(points[0].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[1].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[2].getPosition(), 0.0f, 1.0f)
            };

            std::vector<glm::vec4> colorData {
                points[0].getColor(),
                points[1].getColor(),
                points[2].getColor()
            };

            _pushDrawCall(batch, GL::VertexArray::DrawTarget::Triangles, vertexData, colorData);
        }

    }

}
