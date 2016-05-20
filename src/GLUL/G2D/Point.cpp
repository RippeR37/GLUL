#include <GLUL/G2D/Point.h>


namespace GLUL {

    namespace G2D {

        Point::Point() : _color(glm::vec4 { 1.0f }) { }

        Point::Point(const glm::vec2& position) : Point() {
            *this = position;
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
            std::vector<glm::vec4> vertexData = { glm::vec4 { _position, 0.0f, 1.0f, } };
            std::vector<glm::vec4> colorData = { getColor() };

            _pushDrawCall(geometryBatch, GL::VertexArray::DrawTarget::Points, vertexData, colorData);
        }

    }

}
