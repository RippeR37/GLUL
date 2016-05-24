#include <GLUL/G2D/TexturedRectangle.h>
#include <GLUL/G2D/TexturedQuad.h>


namespace GLUL {

    namespace G2D {

        TexturedRectangle::TexturedRectangle() : _color({ 1.0f }), _texSize({ 1.0f }) {}

        TexturedRectangle::TexturedRectangle(const glm::vec2& position, float size)
            : TexturedRectangle()
        {
            setPosition(position);
            setSize(size);
        }

        TexturedRectangle::TexturedRectangle(const glm::vec2& position, float size, const glm::vec2& texPosition, float texSize)
            : TexturedRectangle(position, size)
        {
            setTexPosition(texPosition);
            setTexSize(texSize);
        }

        TexturedRectangle::TexturedRectangle(const glm::vec2& position, const glm::vec2& size)
            : TexturedRectangle()
        {
            setPosition(position);
            setSize(size);
        }

        TexturedRectangle::TexturedRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec2& texPosition, const glm::vec2& texSize)
            : TexturedRectangle(position, size)
        {
            setTexPosition(texPosition);
            setTexSize(texSize);
        }

        TexturedRectangle::TexturedRectangle(const TexturedPoint& point, float size, float texSize)
            : TexturedRectangle(point.getPosition(), size, point.getTexCoords(), texSize)
        {
            setColor(point.getColor());
        }

        TexturedRectangle::TexturedRectangle(const TexturedPoint& point, const glm::vec2& size, const glm::vec2& texSize)
            : TexturedRectangle(point.getPosition(), size, point.getTexCoords(), texSize)
        {
            setColor(point.getColor());
        }

        void TexturedRectangle::setPosition(const glm::vec2& position) {
            _position = position;
        }

        const glm::vec2& TexturedRectangle::getPosition() const {
            return _position;
        }

        void TexturedRectangle::setSize(float size) {
            setSize({ size, size });
        }

        void TexturedRectangle::setSize(const glm::vec2& size) {
            _size = size;
        }

        const glm::vec2& TexturedRectangle::getSize() const {
            return _size;
        }

        void TexturedRectangle::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void TexturedRectangle::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec4& TexturedRectangle::getColor() const {
            return _color;
        }

        void TexturedRectangle::setTexPosition(const glm::vec2& texPosition) {
            _texPos = texPosition;
        }

        const glm::vec2& TexturedRectangle::getTexPosition() const {
            return _texPos;
        }

        void TexturedRectangle::setTexSize(float texSize) {
            setTexSize({ texSize, texSize });
        }

        void TexturedRectangle::setTexSize(const glm::vec2& texSize) {
            _texSize = texSize;
        }

        const glm::vec2& TexturedRectangle::getTexSize() const {
            return _texSize;
        }

        void TexturedRectangle::_pushToBatch(TexturedGeometryBatch& texGeometryBatch, const GL::Texture& texture) const {
            texGeometryBatch.addPrimitive(
                TexturedQuad {
                    TexturedPoint { getPosition(), getTexPosition(), getColor() },
                    getSize(),
                    getTexSize()
                },
                texture
            );
        }

    }

}
