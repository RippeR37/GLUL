#ifndef UTILS_GL_GUI_TEXTFIELD_H_INCLUDED
#define UTILS_GL_GUI_TEXTFIELD_H_INCLUDED

#include <Utils/GL+/GUI/Component.h>
#include <Utils/GL+/GUI/InnerText.h>
#include <Utils/GL+/GUI/Styles/Border.h>

#include <Utils/GL+/Program.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>

namespace GL {

    namespace GUI {

        class TextField : public Component {
            public:
                TextField(Container& parent);
                TextField(Container* const parent = nullptr);
                ~TextField();

                void render() const;
                void update(double deltaTime);

                void validate() const;

                const glm::vec4& getColor() const;
                float getAlpha() const;
                
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setAlpha(const float alpha);

                InnerText text;
                Style::Border border;

            private:
                std::vector<glm::vec4> getVertices() const;
                
                bool _glInitialized;
                glm::vec4 _color;
                VertexArray _vao;
                VertexBuffer _vbo;

            private:
                static Program& getProgram();
        };

    }

}

#endif
