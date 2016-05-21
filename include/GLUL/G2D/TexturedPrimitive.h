#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/TexturedGeometryBatch.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API TexturedPrimitive {
            public:
                virtual void render(const GL::Texture& texture, unsigned int textureUnit = 0u) const;
                virtual void render(const GL::Program& program, const GL::Texture& texture, unsigned int textureUnit = 0u) const;

                virtual void setColor(const glm::vec3& color) = 0;
                virtual void setColor(const glm::vec4& color) = 0;
                virtual const glm::vec4& getColor() const = 0;

            protected:
                virtual void _pushToBatch(TexturedGeometryBatch& texGeometryBatch, const GL::Texture& texture) const = 0;

                void _pushDrawCall(TexturedGeometryBatch& texGeometryBatch, GL::VertexArray::DrawTarget drawTarget,
                    const std::vector<glm::vec4>& vertexData, const std::vector<glm::vec4>& colorData,
                    const GL::Texture& texture) const;

                friend class TexturedGeometryBatch;
        };

    }

}
