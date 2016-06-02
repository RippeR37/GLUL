#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/Batch.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API Primitive {
            public:
                void render() const;
                void render(const GL::Program& program) const;

                void setColor(const glm::vec3& color);
                virtual void setColor(const glm::vec4& color) = 0;
                virtual const glm::vec4& getColor() const = 0;

            protected:
                virtual void _pushToBatch(Batch& batch) const = 0;

                void _pushDrawCall(Batch& batch, GL::VertexArray::DrawTarget drawTarget,
                    const std::vector<glm::vec2>& vertexData, const std::vector<glm::vec4>& colorData) const;

                friend class Batch;
        };

    }

}
