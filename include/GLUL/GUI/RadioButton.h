#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>
#include <GLUL/GUI/Styles/Border.h>


namespace GLUL {

    namespace GUI  {

        class GLUL_API RadioButtonGroup;

        class GLUL_API RadioButton : public Component {
            public:
                operator bool() const;

                const RadioButton& render() const;
                RadioButton& update(double deltaTime);

                const RadioButton& validate() const;

                const glm::vec4& getColor() const;
                const glm::vec4& getMarkColor() const;
                float getMarkScale() const;
                float getAlpha() const;
                bool getState() const;

                RadioButton& set();
                RadioButton& setColor(const glm::vec3& color);
                RadioButton& setColor(const glm::vec4& color);
                RadioButton& setMarkColor(const glm::vec3& color);
                RadioButton& setMarkColor(const glm::vec4& color);
                RadioButton& setMarkScale(float scale);
                RadioButton& setAlpha(float alpha);
                RadioButton& setSize(const glm::vec2& size);
                RadioButton& setPosition(const glm::vec2& position);
                RadioButton& setPosition(const GLUL::Point& position);
                
                Style::Border border;

            public:
                Event::HandlerAggregator<Event::ValueChange<bool>> onValueChange;

            private:
                RadioButton(RadioButtonGroup& group, Container& parent, bool state = false);
                RadioButton(RadioButtonGroup& group, Container* const parent = nullptr, bool state = false);
                ~RadioButton();

                RadioButton& setState(bool state);

                std::vector<glm::vec4> getVertices() const;

                bool _state;
                bool _glInitialized;
                float _markScale;
                glm::vec4 _color;
                glm::vec4 _markColor;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;
                RadioButtonGroup& _group;

            private:
                static GL::Program& getProgram();

                friend class RadioButtonGroup;
        };

    }

}