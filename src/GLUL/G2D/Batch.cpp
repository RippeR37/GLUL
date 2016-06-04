#include <GLUL/Logger.h>
#include <GLUL/GL++/Context.h>
#include <GLUL/G2D/Batch.h>
#include <GLUL/G2D/Primitive.h>
#include <GLUL/Resources/Programs.h>

#include <glm/vector_relational.hpp>


namespace GLUL {

    namespace G2D {

        Batch::Batch() {
            _initializeVAO();
        }

        Batch::Batch(const Primitive& primitive) : Batch() {
            addPrimitive(primitive);

            compute();
        }

        Batch::Batch(const std::vector<std::reference_wrapper<const Primitive>>& primitives) : Batch() {
            addPrimitives(primitives);

            compute();
        }

        Batch::Batch(const std::initializer_list<std::reference_wrapper<const Primitive>>& primitives) : Batch() {
            addPrimitives(primitives);

            compute();
        }

        void Batch::addPrimitive(const Primitive& primitive) {
            primitive._pushToBatch(*this);
        }

        void Batch::addPrimitives(const std::vector<std::reference_wrapper<const Primitive>>& primitives) {
            for(auto& primitive : primitives)
                addPrimitive(primitive);
        }

        void Batch::addPrimitives(const std::initializer_list<std::reference_wrapper<const Primitive>>& primitives) {
            for(auto& primitive : primitives)
                addPrimitive(primitive);
        }

        void Batch::compute() {
            if(!_vertexData.empty()) {
                // Push data to VBO
                _vbo.bind();
                _vbo.setData(_vertexData);
                _vbo.unbind();

                _cbo.bind();
                _cbo.setData(_colorData);
                _cbo.unbind();
            }
        }

        void Batch::clear() {
            // Clear local data
            _vertexData.clear();
            _colorData.clear();
            _drawCalls.clear();

            // Clear VBOs
            _vbo.bind();
            _vbo.setData(std::vector<glm::vec2> { });
            _vbo.unbind();
            _cbo.bind();
            _cbo.setData(std::vector<glm::vec4> { });
            _cbo.unbind();
        }

        void Batch::clearLocal() {
            _vertexData.clear();
            _colorData.clear();
        }

        void Batch::render() const {
            render(getDefaultProgram());
        }

        void Batch::render(const GL::Program& program) const {
            static glm::ivec2 windowSize;

            program.use();
            _vao.bind();

            if(glm::any(glm::notEqual(windowSize, GL::Context::Current->getViewportSize()))) {
                windowSize = GL::Context::Current->getViewportSize();
                program["windowSize"].setVec<glm::vec2>(windowSize);
            }

            for(const auto& drawCall : _drawCalls) {
                _vao.setDrawOffset(drawCall.offset);
                _vao.setDrawCount(drawCall.count);
                _vao.setDrawTarget(drawCall.target);

                _vao.drawArrays();
            }

            _vao.unbind();
            program.unbind();
        }

        void Batch::_initializeVAO() {
            _vao.bind();
                _vbo.bind();
                _vao.setAttribPointers({ GL::VertexAttrib(0, 2, GL_FLOAT, 0, nullptr) });
                _vbo.unbind();

                _cbo.bind();
                _vao.setAttribPointers({ GL::VertexAttrib(1, 4, GL_FLOAT, 0, nullptr) });
                _cbo.unbind();
            _vao.unbind();
        }


        void Batch::_pushCall(
            GL::VertexArray::DrawTarget drawTarget,
            const std::vector<glm::vec2>& vertexData,
            const std::vector<glm::vec4>& colorData)
        {
            // Check if local data was not cleared
            if(_vertexData.empty() && !_drawCalls.empty())
                _drawCalls.clear();

            // Make sure that same ammount of vertex and color data will be added
            if(vertexData.size() != colorData.size()) {
                GLUL::Log::LibraryStream().logError("[G2D] Attempt to push diffrent ammount of vertex and color data.");
                return;
            }

            // Push draw call
            if(_drawCalls.empty() || _drawCalls.back().target != drawTarget) {
                _drawCalls.push_back({
                    static_cast<GLint>(_vertexData.size()),
                    static_cast<GLsizei>(vertexData.size()),
                    drawTarget
                });
            } else {
                _drawCalls.back().count += vertexData.size();
            }

            // Push vertex and color data
            _vertexData.reserve(_vertexData.size() + vertexData.size());
            _colorData.reserve(_colorData.size() + colorData.size());
            _vertexData.insert(_vertexData.end(), vertexData.begin(), vertexData.end());
            _colorData.insert(_colorData.end(), colorData.begin(), colorData.end());
        }

        const GL::Program& Batch::getDefaultProgram() {
            return Resources::Programs::Get("G2D/Default.vp", "G2D/Default.fp", true);
        }

    }

}
