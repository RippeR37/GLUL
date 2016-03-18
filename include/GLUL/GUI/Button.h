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

        class GLUL_API Button : public Component {
            public:
                Button(Container& parent);
                Button(Container* const parent = nullptr);
                ~Button();

                const Button& render() const;
                Button& update(double deltaTime);

                const Button& validate() const;

                const glm::vec4& getColor() const;
                float getAlpha() const;
                
                Button& setColor(const glm::vec3& color);
                Button& setColor(const glm::vec4& color);
                Button& setAlpha(float alpha);
                Button& setSize(const glm::vec2& size);
                Button& setPosition(const glm::vec2& position);
                Button& setPosition(const GLUL::Point& position);

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
