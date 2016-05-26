#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>

#include <glm/vec4.hpp>

#include <functional>
#include <initializer_list>
#include <vector>


namespace GLUL {

    namespace G2D {

        class GLUL_API Primitive;

        class GLUL_API Batch {
            public:
                struct DrawCall {
                    GLint offset;
                    GLsizei count;
                    GL::VertexArray::DrawTarget target;
                };

            public:
                Batch();
                Batch(const Primitive& primitive);
                Batch(const std::vector<std::reference_wrapper<const Primitive>>& primitives);
                Batch(const std::initializer_list<std::reference_wrapper<const Primitive>>& primitives);

                void addPrimitive(const Primitive& primitive);
                void addPrimitives(const std::vector<std::reference_wrapper<const Primitive>>& primitives);
                void addPrimitives(const std::initializer_list<std::reference_wrapper<const Primitive>>& primitives);

                void compute();

                void clear();
                void clearLocal();

                void render() const;
                void render(const GL::Program& program) const;

            private:
                void _initializeVAO();
                void _pushCall(GL::VertexArray::DrawTarget drawTarget,
                    const std::vector<glm::vec4>& vertexData, const std::vector<glm::vec4>& colorData);

                static GL::Program& getDefaultProgram();

                std::vector<DrawCall> _drawCalls;
                std::vector<glm::vec4> _vertexData;
                std::vector<glm::vec4> _colorData;
                mutable GL::Program _program;
                mutable GL::VertexArray _vao;
                mutable GL::VertexBuffer _vbo;
                mutable GL::VertexBuffer _cbo;

                friend class Primitive;
                friend class Shape;
        };

    }

}
