#include <GLUL/Logger.h>
#include <GLUL/GL++/Context.h>
#include <GLUL/GL++/Texture.h>
#include <GLUL/G2D/TexturedGeometryBatch.h>
#include <GLUL/G2D/TexturedPrimitive.h>

#include <glm/vector_relational.hpp>


namespace GLUL {

    namespace G2D {

        TexturedGeometryBatch::TexturedGeometryBatch() {
            _initializeVAO();
        }

        TexturedGeometryBatch::TexturedGeometryBatch(const TexturedPrimitive& primitive, const GL::Texture& texture)
            : TexturedGeometryBatch()
        {
            addPrimitive(primitive, texture);
            compute();
        }

        TexturedGeometryBatch::TexturedGeometryBatch(const std::vector<TexturedPrimitiveRef>& primitives, const GL::Texture& texture)
            : TexturedGeometryBatch()
        {
            addPrimitives(primitives, texture);
            compute();
        }

        TexturedGeometryBatch::TexturedGeometryBatch(const std::vector< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives)
            : TexturedGeometryBatch()
        {
            addPrimitives(primitives);
            compute();
        }

        TexturedGeometryBatch::TexturedGeometryBatch(const std::initializer_list< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives)
            : TexturedGeometryBatch()
        {
            addPrimitives(primitives);
            compute();
        }

        void TexturedGeometryBatch::addPrimitive(const TexturedPrimitive& primitive, const GL::Texture& texture) {
            primitive._pushToBatch(*this, texture);
        }

        void TexturedGeometryBatch::addPrimitives(const std::vector<TexturedPrimitiveRef>& primitives, const GL::Texture& texture) {
            for(auto& primitive : primitives)
                addPrimitive(primitive, texture);
        }

        void TexturedGeometryBatch::addPrimitives(const std::vector< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives) {
            for(auto& pair : primitives)
                addPrimitive(pair.first, pair.second);
        }

        void TexturedGeometryBatch::addPrimitives(const std::initializer_list< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives) {
            for(auto& pair : primitives)
                addPrimitive(pair.first, pair.second);
        }

        void TexturedGeometryBatch::compute() {
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

        void TexturedGeometryBatch::clear() {
            // Clear local data
            _vertexData.clear();
            _colorData.clear();
            _drawCalls.clear();

            // Clear VBOs
            _vbo.bind();
            _vbo.setData(std::vector<glm::vec4> { });
            _vbo.unbind();
            _cbo.bind();
            _cbo.setData(std::vector<glm::vec4> { });
            _cbo.unbind();
        }

        void TexturedGeometryBatch::clearLocal() {
            _vertexData.clear();
            _colorData.clear();
        }

        void TexturedGeometryBatch::render(unsigned int textureUnit) const {
            render(getDefaultProgram(), textureUnit);
        }

        void TexturedGeometryBatch::render(const GL::Program& program, unsigned int textureUnit) const {
            static glm::ivec2 windowSize;

            program.use();
            _vao.bind();

            // TODO: HACK: change it with Context/Texture class
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            program["texSampler"].setSampler(textureUnit);

            if(glm::any(glm::notEqual(windowSize, GL::Context::Current->getViewportSize()))) {
                windowSize = GL::Context::Current->getViewportSize();
                program["windowSize"].setVec<glm::vec2>(windowSize);
            }

            for(const auto& drawCall : _drawCalls) {
                _vao.setDrawOffset(drawCall.offset);
                _vao.setDrawCount(drawCall.count);
                _vao.setDrawTarget(drawCall.target);

                drawCall.texture.get().bind();
                _vao.drawArrays();
                drawCall.texture.get().unbind();
            }

            _vao.unbind();
            program.unbind();
        }

        void TexturedGeometryBatch::_initializeVAO() {
            _vao.bind();
                _vbo.bind();
                _vao.setAttribPointers({ GL::VertexAttrib(0, 4, GL_FLOAT, 0, nullptr) });
                _vbo.unbind();

                _cbo.bind();
                _vao.setAttribPointers({ GL::VertexAttrib(1, 4, GL_FLOAT, 0, nullptr) });
                _cbo.unbind();
            _vao.unbind();
        }

        void TexturedGeometryBatch::_pushCall(GL::VertexArray::DrawTarget drawTarget,
            const std::vector<glm::vec4>& vertexData,
            const std::vector<glm::vec4>& colorData,
            const GL::Texture& texture)
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
            if(_drawCalls.empty() || _drawCalls.back().target != drawTarget || _drawCalls.back().texture.get().getID() != texture.getID()) {
                _drawCalls.push_back({
                    static_cast<GLint>(_vertexData.size()),
                    static_cast<GLsizei>(vertexData.size()),
                    drawTarget,
                    texture
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

        GL::Program& TexturedGeometryBatch::getDefaultProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/G2D/Textured.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/G2D/Textured.fp", GL::Shader::Type::FragmentShader)
            );

            return program;
        }

    }

}
