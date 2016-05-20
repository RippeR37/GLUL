#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/GeometryBatch.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace GLUL {

    namespace G2D {

        class GLUL_API Primitive {
            public:
                void setColor(const glm::vec3& color);
                virtual void setColor(const glm::vec4& color) = 0;
                virtual const glm::vec4& getColor() const = 0;

            protected:
                virtual void _pushToBatch(GeometryBatch& geometryBatch) const = 0;

                void _pushDrawCall(GeometryBatch& geometryBatch, GL::VertexArray::DrawTarget drawTarget,
                    const std::vector<glm::vec4>& vertexData, const std::vector<glm::vec4>& colorData) const;

                friend class GeometryBatch;
        };

    }

}
