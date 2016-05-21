#include <GLUL/G2D/TexturedTriangle.h>


namespace GLUL {

    namespace G2D {

        TexturedTriangle::TexturedTriangle() : points({}) { }

        TexturedTriangle::TexturedTriangle(
            const TexturedPoint& point1,
            const TexturedPoint& point2,
            const TexturedPoint& point3)
        {
            points[0] = point1;
            points[1] = point2;
            points[2] = point3;
        }

        void TexturedTriangle::setColor(const glm::vec3& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        void TexturedTriangle::setColor(const glm::vec4& color) {
            for(auto& point : points)
                point.setColor(color);
        }

        const glm::vec4& TexturedTriangle::getColor() const {
            return points[0].getColor();
        }

        void TexturedTriangle::_pushToBatch(TexturedGeometryBatch& texGeometryBatch, const GL::Texture& texture) const {
            std::vector<glm::vec4> vertexData {
                glm::vec4 { points[0].getPosition(), points[0].getTexCoords() },
                glm::vec4 { points[1].getPosition(), points[1].getTexCoords() },
                glm::vec4 { points[2].getPosition(), points[2].getTexCoords() }
            };

            std::vector<glm::vec4> colorData {
                points[0].getColor(),
                points[1].getColor(),
                points[2].getColor()
            };

            _pushDrawCall(texGeometryBatch, GL::VertexArray::DrawTarget::Triangles, vertexData, colorData, texture);
        }

    }

}
