#include <GLUL/G2D/Quad.h>


namespace GLUL {

    namespace G2D {

        Quad::Quad() { }

        Quad::Quad(const Point& point1, const Point& point2, const Point& point3, const Point& point4) {
            points[0] = point1;
            points[1] = point2;
            points[2] = point3;
            points[3] = point4;
        }

        Quad::Quad(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3, const glm::vec2& position4)
            : Quad(Point(position1), Point(position2), Point(position3), Point(position4)) { }

        void Quad::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& Quad::getColor() const {
            return points[0].getColor();
        }

        void Quad::_pushToBatch(GeometryBatch& geometryBatch) const {
            std::vector<glm::vec4> vertexData {
                glm::vec4(points[0].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[1].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[2].getPosition(), 0.0f, 1.0f),

                glm::vec4(points[0].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[2].getPosition(), 0.0f, 1.0f),
                glm::vec4(points[3].getPosition(), 0.0f, 1.0f),
            };

            std::vector<glm::vec4> colorData {
                points[0].getColor(),
                points[1].getColor(),
                points[2].getColor(),

                points[0].getColor(),
                points[2].getColor(),
                points[3].getColor()
            };

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Triangles, vertexData, colorData);
        }

    }

}
