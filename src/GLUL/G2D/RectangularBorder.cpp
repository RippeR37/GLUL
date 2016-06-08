#include <GLUL/G2D/Rectangle.h>
#include <GLUL/G2D/RectangularBorder.h>


namespace GLUL {

    namespace G2D {

        RectangularBorder::RectangularBorder()
            : RectangularBorder({ 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f }) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize)
            : RectangularBorder(position, glm::vec2 { rectangleSize }, glm::vec2 { borderSize }) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize, const glm::vec3& color)
            : RectangularBorder(position, glm::vec2 { rectangleSize }, glm::vec2 { borderSize }, color) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, float rectangleSize, float borderSize, const glm::vec4& color)
            : RectangularBorder(position, glm::vec2 { rectangleSize }, glm::vec2 { borderSize }, color) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize)
            : RectangularBorder(position, rectangleSize, borderSize, glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f }) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize, const glm::vec3& color)
            : RectangularBorder(position, rectangleSize, borderSize, glm::vec4 { color, 1.0f }) { }

        RectangularBorder::RectangularBorder(const glm::vec2& position, const glm::vec2& rectangleSize, const glm::vec2& borderSize, const glm::vec4& color)
            : _position(position), _rectangleSize(rectangleSize), _size(borderSize), _color(color) { }

        RectangularBorder::RectangularBorder(const Point& point, float rectangleSize, float borderSize)
            : RectangularBorder(point.getPosition(), rectangleSize, borderSize, point.getColor()) { }

        RectangularBorder::RectangularBorder(const Point& point, const glm::vec2& rectangleSize, const glm::vec2& borderSize)
            : RectangularBorder(point.getPosition(), rectangleSize, borderSize, point.getColor()) { }

        void RectangularBorder::setPosition(const glm::vec2& position) {
            _position = position;
        }

        void RectangularBorder::setSize(float size) {
            setSize(glm::vec2 { size });
        }

        void RectangularBorder::setSize(const glm::vec2& size) {
            _size = size;
        }

        void RectangularBorder::setRectangleSize(float rectangleSize) {
            setRectangleSize(glm::vec2 { rectangleSize });
        }

        void RectangularBorder::setRectangleSize(const glm::vec2& rectangleSize) {
            _rectangleSize = rectangleSize;
        }

        void RectangularBorder::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec2& RectangularBorder::getPosition() const {
            return _position;
        }

        const glm::vec4& RectangularBorder::getColor() const {
            return _color;
        }

        const glm::vec2& RectangularBorder::getSize() const {
            return _size;
        }

        const glm::vec2& RectangularBorder::getRectangleSize() const {
            return _rectangleSize;
        }

        void RectangularBorder::_pushToBatch(Batch& batch) const {
            // Up (whole line)
            batch.addPrimitive(Rectangle {
                getPosition() + glm::vec2 { -getSize().x, getRectangleSize().y },
                glm::vec2 { getRectangleSize().x + 2 * getSize().x, getSize().y },
                getColor()
            });

            // Bottom (whole line)
            batch.addPrimitive(Rectangle {
                getPosition() - getSize(),
                glm::vec2 { getRectangleSize().x + 2 * getSize().x, getSize().y },
                getColor()
            });

            // Left (without corners)
            batch.addPrimitive(Rectangle {
                getPosition() - glm::vec2 { getSize().x, 0.0f },
                glm::vec2 { getSize().x, getRectangleSize().y },
                getColor()
            });

            // Right (without corners)
            batch.addPrimitive(Rectangle {
                getPosition() + glm::vec2 { getRectangleSize().x, 0.0f },
                glm::vec2 { getSize().x, getRectangleSize().y },
                getColor()
            });
        }

    }

}
