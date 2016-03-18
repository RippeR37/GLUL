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

                const TextField& render() const;
                TextField& update(double deltaTime);

                const TextField& validate() const;

                const glm::vec4& getColor() const;
                float getAlpha() const;
                const std::string& getValue() const;
                
                TextField& setColor(const glm::vec3& color);
                TextField& setColor(const glm::vec4& color);
                TextField& setAlpha(const float alpha);
                TextField& setValue(const std::string& value);
                TextField& setSize(const glm::vec2& size);
                TextField& setPosition(const glm::vec2& position);
                TextField& setPosition(const GLUL::Point& position);

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
