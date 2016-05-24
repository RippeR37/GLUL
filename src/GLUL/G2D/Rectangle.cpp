#include <GLUL/G2D/Rectangle.h>
#include <GLUL/G2D/Quad.h>


namespace GLUL {

    namespace G2D {

        Rectangle::Rectangle() : _color(glm::vec4 { 1.0f }) { }

        Rectangle::Rectangle(const glm::vec2& position, float size) : Rectangle() {
            setPosition(position);
            setSize(size);
        }

        Rectangle::Rectangle(const glm::vec2& position, float size, const glm::vec3& color)
            : Rectangle(position, size)
        {
            setColor(color);
        }

        Rectangle::Rectangle(const glm::vec2& position, float size, const glm::vec4& color)
            : Rectangle(position, size)
        {
            setColor(color);
        }

        Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size) : Rectangle() {
            setPosition(position);
            setSize(size);
        }

        Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
            : Rectangle(position, size)
        {
            setColor(color);
        }

        Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
            : Rectangle(position, size)
        {
            setColor(color);
        }

        Rectangle::Rectangle(const Point& point, float size)
            : Rectangle(point.getPosition(), size, point.getColor()) { }

        Rectangle::Rectangle(const Point& point, const glm::vec2& size)
            : Rectangle(point.getPosition(), size, point.getColor()) { }

        void Rectangle::setPosition(const glm::vec2& position) {
            _position = position;
        }

        const glm::vec2& Rectangle::getPosition() const {
            return _position;
        }

        void Rectangle::setSize(float size) {
            setSize({ size, size });
        }

        void Rectangle::setSize(const glm::vec2& size) {
            _size = size;
        }

        const glm::vec2& Rectangle::getSize() const {
            return _size;
        }

        void Rectangle::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec4& Rectangle::getColor() const {
            return _color;
        }

        void Rectangle::_pushToBatch(GeometryBatch& geometryBatch) const {
            geometryBatch.addPrimitive({
                Quad {
                    Point { getPosition(), getColor() },
                    getSize()
                }
            });
        }

    }

}
