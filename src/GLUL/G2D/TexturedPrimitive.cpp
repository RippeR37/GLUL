#include <GLUL/G2D/TexturedPrimitive.h>


namespace GLUL {

    namespace G2D {

        void TexturedPrimitive::render(const GL::Texture& texture, unsigned int textureUnit) const {
            render(TexturedBatch::getDefaultProgram(), texture, textureUnit);
        }

        void TexturedPrimitive::render(const GL::Program& program, const GL::Texture& texture, unsigned int textureUnit) const {
            static TexturedBatch geometry;

            geometry.addPrimitive(*this, texture);
            geometry.compute();
            geometry.render(program, textureUnit);
            geometry.clear();
        }

        void TexturedPrimitive::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void TexturedPrimitive::_pushDrawCall(
            TexturedBatch& texBatch,
            GL::VertexArray::DrawTarget drawTarget,
            const std::vector<glm::vec4>& vertexData,
            const std::vector<glm::vec4>& colorData,
            const GL::Texture& texture) const
        {
            texBatch._pushCall(drawTarget, vertexData, colorData, texture);
        }

    }

}
