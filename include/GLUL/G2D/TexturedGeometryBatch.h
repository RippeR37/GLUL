#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/Texture.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>

#include <glm/vec4.hpp>

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>


namespace GLUL {

    namespace G2D {

        class GLUL_API Font;
        class GLUL_API Text;
        class GLUL_API TexturedPrimitive;

        class GLUL_API TexturedGeometryBatch {
            public:
                using FontRef = std::reference_wrapper<const Font>;
                using TextRef = std::reference_wrapper<const Text>;
                using TexturedPrimitiveRef = std::reference_wrapper<const TexturedPrimitive>;
                using TextureRef = std::reference_wrapper<const GL::Texture>;

                struct DrawCall {
                    DrawCall(GLint offset, GLsizei count, GL::VertexArray::DrawTarget target, TextureRef texture)
                        : offset(offset), count(count), target(target), texture(texture) { }

                    GLint offset;
                    GLsizei count;
                    GL::VertexArray::DrawTarget target;
                    std::reference_wrapper<const GL::Texture> texture;
                };

            public:
                TexturedGeometryBatch();

                TexturedGeometryBatch(const TexturedPrimitive& primitive, const GL::Texture& texture);
                TexturedGeometryBatch(const std::vector<TexturedPrimitiveRef>& primitives, const GL::Texture& texture);
                TexturedGeometryBatch(const std::vector< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives);
                TexturedGeometryBatch(const std::initializer_list< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives);

                TexturedGeometryBatch(const Text& text, const Font& font);
                TexturedGeometryBatch(const std::vector<TextRef>& texts, const Font& font);
                TexturedGeometryBatch(const std::vector< std::pair<TextRef, FontRef> >& texts);
                TexturedGeometryBatch(const std::initializer_list< std::pair<TextRef, FontRef> >& texts);


                void addPrimitive(const TexturedPrimitive& primitive, const GL::Texture& texture);
                void addPrimitives(const std::vector<TexturedPrimitiveRef>& primitives, const GL::Texture& texture);
                void addPrimitives(const std::vector< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives);
                void addPrimitives(const std::initializer_list< std::pair<TexturedPrimitiveRef, TextureRef> >& primitives);

                void addText(const Text& text, const Font& font);
                void addTexts(const std::vector<TextRef>& texts, const Font& font);
                void addTexts(const std::vector< std::pair<TextRef, FontRef> >& texts);
                void addTexts(const std::initializer_list< std::pair<TextRef, FontRef> >& texts);

                void compute();

                void clear();
                void clearLocal();

                void render(unsigned int textureUnit = 0u) const;
                void render(const GL::Program& program, unsigned int textureUnit = 0u) const;

            private:
                void _initializeVAO();
                void _pushCall(GL::VertexArray::DrawTarget drawTarget,
                    const std::vector<glm::vec4>& vertexData,
                    const std::vector<glm::vec4>& colorData,
                    const GL::Texture& texture);

                static GL::Program& getDefaultProgram();

                std::vector<DrawCall> _drawCalls;
                std::vector<glm::vec4> _vertexData;
                std::vector<glm::vec4> _colorData;
                mutable GL::Program _program;
                mutable GL::VertexArray _vao;
                mutable GL::VertexBuffer _vbo;
                mutable GL::VertexBuffer _cbo;

                friend class Text;
                friend class TexturedPrimitive;
                friend class TexturedShape;
        };

    }

}
