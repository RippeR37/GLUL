#include <GLUL/G2D/TexturedPoint.h>


namespace GLUL {

    namespace G2D {

        TexturedPoint::TexturedPoint() : _color(glm::vec4 { 1.0f }) { }

        TexturedPoint::TexturedPoint(const glm::vec2& position) : TexturedPoint() {
            setPosition(position);
        }

        TexturedPoint::TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords)
            : TexturedPoint(position)
        {
            setTexCoords(texCoords);
        }

        TexturedPoint::TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords, const glm::vec3& color)
            : TexturedPoint(position, texCoords, glm::vec4 { color, 1.0f }) { }

        TexturedPoint::TexturedPoint(const glm::vec2& position, const glm::vec2& texCoords, const glm::vec4& color)
            : TexturedPoint(Point { position, color }, texCoords) { }

        TexturedPoint::TexturedPoint(const Point& point) : TexturedPoint() {
            setPosition(point);
            setColor(point.getColor());
        }

        TexturedPoint::TexturedPoint(const Point& point, const glm::vec2& texCoords)
            : TexturedPoint(point)
        {
            setTexCoords(texCoords);
        }

        void TexturedPoint::setPosition(const glm::vec2& position) {
            _position = position;
        }

        void TexturedPoint::setPosition(const Point& point) {
            setPosition(point.getPosition());
        }

        void TexturedPoint::setPosition(const TexturedPoint& point) {
            setPosition(point.getPosition());
        }

        void TexturedPoint::setTexCoords(const glm::vec2& texCoords) {
            _texCoords = texCoords;
        }

        void TexturedPoint::setTexCoords(const TexturedPoint& point) {
            setTexCoords(point.getTexCoords());
        }

        void TexturedPoint::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void TexturedPoint::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec2& TexturedPoint::getPosition() const {
            return _position;
        }

        const glm::vec2& TexturedPoint::getTexCoords() const {
            return _texCoords;
        }

        const glm::vec4& TexturedPoint::getColor() const {
            return _color;
        }

    }

}
