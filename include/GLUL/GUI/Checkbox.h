#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Styles/Border.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API Checkbox : public Component {
            public:
                Checkbox(Container& parent, bool state = false);
                Checkbox(Container* const parent = nullptr, bool state = false);
                ~Checkbox();

                operator bool() const;

                void render() const;
                void update(double deltaTime);

                void validate() const;

                const glm::vec4& getColor() const;
                const glm::vec4& getMarkColor() const;
                float getMarkScale() const;
                float getAlpha() const;
                bool getState() const;
                
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setMarkColor(const glm::vec3& color);
                void setMarkColor(const glm::vec4& color);
                void setMarkScale(float scale);
                void setAlpha(float alpha);
                void setState(bool state);

                bool switchState();

                Style::Border border;

            private:
                std::vector<glm::vec4> getVertices() const;
                
                bool _state;
                bool _glInitialized;
                float _markScale;
                glm::vec4 _color;
                glm::vec4 _markColor;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;

            private:
                static GL::Program& getProgram();
        };

    }

}
