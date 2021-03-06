#include <GLUL/G2D/Triangle.h>
#include <GLUL/G2D/Quad.h>


namespace GLUL {

    namespace G2D {

        Quad::Quad() : points({}) {}

        Quad::Quad(const Point& point1, const Point& point2, const Point& point3, const Point& point4) {
            points[0] = point1;
            points[1] = point2;
            points[2] = point3;
            points[3] = point4;
        }

        Quad::Quad(const Point& bottomLeftPoint, float size) {
            setSquare(bottomLeftPoint, size);
        }

        Quad::Quad(const Point& bottomLeftPoint, const glm::vec2& size) {
            setRectangle(bottomLeftPoint, size);
        }

        Quad::Quad(const glm::vec2& position1, const glm::vec2& position2, const glm::vec2& position3, const glm::vec2& position4)
            : Quad(Point { position1 }, Point { position2 }, Point { position3 }, Point { position4 }) { }

        Quad::Quad(const glm::vec2& bottomLeftPosition, float size)
            : Quad(Point { bottomLeftPosition }, size) { }

        Quad::Quad(const glm::vec2& bottomLeftPosition, const glm::vec2& size)
            : Quad(Point { bottomLeftPosition }, size) { }

        void Quad::setSquare(const Point& bottomLeftPoint, float size) {
            setRectangle(bottomLeftPoint, { size, size });
        }

        void Quad::setRectangle(const Point& bottomLeftPoint, const glm::vec2& size) {
            Point currentPoint = bottomLeftPoint;

            points[0] = currentPoint;

            currentPoint.setPosition(bottomLeftPoint.getPosition() + glm::vec2 { size.x, 0.0f   });
            points[1] = currentPoint;

            currentPoint.setPosition(bottomLeftPoint.getPosition() + glm::vec2 { size.x, size.y });
            points[2] = currentPoint;

            currentPoint.setPosition(bottomLeftPoint.getPosition() + glm::vec2 { 0.0f,   size.y });
            points[3] = currentPoint;
        }

        void Quad::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& Quad::getColor() const {
            return points[0].getColor();
        }

        void Quad::_pushToBatch(Batch& batch) const {
            batch.addPrimitive(Triangle { points[0], points[1], points[2] });
            batch.addPrimitive(Triangle { points[0], points[2], points[3] });
        }

    }

}
