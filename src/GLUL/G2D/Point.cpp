#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Quad.h>


namespace GLUL {

    namespace G2D {

        Point::Point(unsigned int size) : _color(glm::vec4 { 1.0f }), size(size) { }

        Point::Point(const glm::vec2& position, unsigned int size) : Point(size) {
            setPosition(position);
        }

        Point& Point::operator=(const glm::vec2& position) {
            setPosition(position);

            return *this;
        }

        void Point::setPosition(const glm::vec2& position) {
            _position = position;
        }

        void Point::setPosition(const Point& point) {
            _position = point.getPosition();
        }

        const glm::vec2& Point::getPosition() const {
            return _position;
        }

        void Point::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec4& Point::getColor() const {
            return _color;
        }

        void Point::_pushToBatch(GeometryBatch& geometryBatch) const {
            Quad quad;
            Point bottomLeftPoint = *this;

            bottomLeftPoint.setPosition(getPosition() - glm::vec2 { static_cast<float>((size / 2)) });
            quad.setSquare(bottomLeftPoint, static_cast<float>(size));

            geometryBatch.addPrimitive(quad);
        }

    }

}
