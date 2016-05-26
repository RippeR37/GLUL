#include <GLUL/G2D/TexturedTriangle.h>
#include <GLUL/G2D/TexturedQuad.h>


namespace GLUL {

    namespace G2D {

        TexturedQuad::TexturedQuad() : points({}) { }

        TexturedQuad::TexturedQuad(
            const TexturedPoint& point1,
            const TexturedPoint& point2,
            const TexturedPoint& point3,
            const TexturedPoint& point4)
        {
            points[0] = point1;
            points[1] = point2;
            points[2] = point3;
            points[3] = point4;
        }

        TexturedQuad::TexturedQuad(const TexturedPoint& bottomLeftPoint, float size, float texSize) {
            setSquare(bottomLeftPoint, size, texSize);
        }

        TexturedQuad::TexturedQuad(const TexturedPoint& bottomLeftPoint, const glm::vec2& size, const glm::vec2& texSize) {
            setRectangle(bottomLeftPoint, size, texSize);
        }

        void TexturedQuad::setSquare(const TexturedPoint& bottomLeftPoint, float size, float texSize) {
            setRectangle(bottomLeftPoint, { size, size }, { texSize, texSize });
        }

        void TexturedQuad::setRectangle(const TexturedPoint& bottomLeftPoint,
            const glm::vec2& size, const glm::vec2& texSize)
        {
            TexturedPoint currentPoint = bottomLeftPoint;

            points[0] = currentPoint;

            currentPoint.setPosition( bottomLeftPoint.getPosition()  + glm::vec2 { size.x, 0.0f });
            currentPoint.setTexCoords(bottomLeftPoint.getTexCoords() + glm::vec2 { texSize.x, 0.0f });
            points[1] = currentPoint;

            currentPoint.setPosition( bottomLeftPoint.getPosition()  + size);
            currentPoint.setTexCoords(bottomLeftPoint.getTexCoords() + texSize);
            points[2] = currentPoint;

            currentPoint.setPosition( bottomLeftPoint.getPosition()  + glm::vec2 { 0.0f, size.y});
            currentPoint.setTexCoords(bottomLeftPoint.getTexCoords() + glm::vec2 { 0.0f, texSize.y });
            points[3] = currentPoint;
        }

        void TexturedQuad::setColor(const glm::vec3& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        void TexturedQuad::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& TexturedQuad::getColor() const {
            return points[0].getColor();
        }

        void TexturedQuad::_pushToBatch(TexturedBatch& texBatch, const GL::Texture& texture) const {
            texBatch.addPrimitive(TexturedTriangle { points[0], points[1], points[2] }, texture);
            texBatch.addPrimitive(TexturedTriangle { points[0], points[2], points[3] }, texture);
        }

    }

}
