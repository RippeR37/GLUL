#include <GLUL/G2D/Primitive.h>


namespace GLUL {

    namespace G2D {

        void Primitive::render() const {
            render(GeometryBatch::getDefaultProgram());
        }

        void Primitive::render(const GL::Program& program) const {
            static GeometryBatch geometry;

            geometry.addPrimitive(*this);
            geometry.compute();
            geometry.render(program);
            geometry.clear();
        }

        void Primitive::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void Primitive::_pushDrawCall(GeometryBatch& geometryBatch,
            GL::VertexArray::DrawTarget drawTarget,
            const std::vector<glm::vec4>& vertexData,
            const std::vector<glm::vec4>& colorData) const
        {
            geometryBatch._pushCall(drawTarget, vertexData, colorData);
        }

    }

}
