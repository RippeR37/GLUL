#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.h>
#include <GLUL/GUI/Styles/Border.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API ProgressBar : public Component {
            public:
                ProgressBar(Container& parent, float progress = 0.0f);
                ProgressBar(Container* const parent = nullptr, float progress = 0.0f);
                ~ProgressBar();

                operator float() const;

                const ProgressBar& render() const;
                ProgressBar& update(double deltaTime);

                const ProgressBar& validate() const;

                const glm::vec4& getColor() const;
                const glm::vec4& getBackgroundColor() const;
                float getAlpha() const;
                float getBackgroundAlpha() const;
                float getProgress() const;

                ProgressBar& setColor(const glm::vec3& color);
                ProgressBar& setColor(const glm::vec4& color);
                ProgressBar& setBackgroundColor(const glm::vec3& color);
                ProgressBar& setBackgroundColor(const glm::vec4& color);
                ProgressBar& setAlpha(float alpha);
                ProgressBar& setBackgroundAlpha(float alpha);
                ProgressBar& setProgress(float progress);
                ProgressBar& setSize(const glm::vec2& size);
                ProgressBar& setPosition(const glm::vec2& position);
                ProgressBar& setPosition(const GLUL::Point& position);

                ProgressBar& increaseProgress(float value);
                ProgressBar& decreaseProgress(float value);

                Style::Border border;

            public:
                Event::HandlerAggregator<Event::ValueChange> onValueChange;

            private:
                std::vector<glm::vec4> getVertices() const;

                bool _glInitialized;
                float _progress;
                glm::vec4 _color;
                glm::vec4 _backgroundColor;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;

            private:
                static GL::Program& getProgram();
        };

    }

}
