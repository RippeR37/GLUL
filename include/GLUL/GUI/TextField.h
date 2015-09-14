#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/InnerText.h>
#include <GLUL/GUI/Styles/Border.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API TextField : public Component {
            public:
                TextField(Container& parent);
                TextField(Container* const parent = nullptr);
                ~TextField();

                void render() const;
                void update(double deltaTime);

                void validate() const;

                const glm::vec4& getColor() const;
                float getAlpha() const;
                const std::string& getValue() const;
                
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setAlpha(const float alpha);
                void setValue(const std::string& value);

                InnerText text;
                Style::Border border;

            private:
                std::vector<glm::vec4> getVertices() const;
                
                bool _glInitialized;
                glm::vec4 _color;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;

            private:
                static GL::Program& getProgram();
        };

    }

}
