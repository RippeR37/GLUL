#include <GLUL/G2D/Line.h>


namespace GLUL {

    namespace G2D {

        Line::Line() { }

        Line::Line(const Point& point1, const Point& point2) {
            points[0] = point1;
            points[1] = point2;
        }

        Line::Line(const glm::vec2& position1, const glm::vec2& position2) : Line(Point(position1), Point(position2)) { }

        void Line::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& Line::getColor() const {
            return points[0].getColor();
        }

        void Line::_pushToBatch(GeometryBatch& geometryBatch) const {
            std::vector<glm::vec4> vertexData {
                glm::vec4(points[0].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[1].getPosition(), 0.0f, 1.0f)
            };

            std::vector<glm::vec4> colorData {
                points[0].getColor(),
                points[1].getColor()
            };

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Lines, vertexData, colorData);
        }

    }

}
