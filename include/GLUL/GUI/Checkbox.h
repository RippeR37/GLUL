#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>
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

                const Checkbox& render() const;
                Checkbox& update(double deltaTime);

                const Checkbox& validate() const;

                const glm::vec4& getColor() const;
                const glm::vec4& getMarkColor() const;
                float getMarkScale() const;
                float getAlpha() const;
                bool getState() const;
                
                Checkbox& setColor(const glm::vec3& color);
                Checkbox& setColor(const glm::vec4& color);
                Checkbox& setMarkColor(const glm::vec3& color);
                Checkbox& setMarkColor(const glm::vec4& color);
                Checkbox& setMarkScale(float scale);
                Checkbox& setAlpha(float alpha);
                Checkbox& setState(bool state);
                Checkbox& setSize(const glm::vec2& size);
                Checkbox& setPosition(const glm::vec2& position);

                bool switchState();

                Style::Border border;

            public:
                Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

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
