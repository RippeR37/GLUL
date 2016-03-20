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

        class GLUL_API Slider : public Component {
        public:
            Slider(Container& parent, float min = 0.0f, float max = 1.0f, float value = 0.0f);
            Slider(Container* const parent = nullptr, float min = 0.0f, float max = 1.0f, float value = 0.0f);
            ~Slider();

            operator float() const;

            const Slider& render() const;
            Slider& update(double deltaTime);

            const Slider& validate() const;

            const glm::vec4& getColor() const;
            const glm::vec4& getBackgroundColor() const;
            float getAlpha() const;
            float getBackgroundAlpha() const;
            float getValue() const;
            float getMin() const;
            float getMax() const;

            float normalizeValue(float value) const;
            float denormalizeValue(float normalizedValue) const;

            Slider& setColor(const glm::vec3& color);
            Slider& setColor(const glm::vec4& color);
            Slider& setBackgroundColor(const glm::vec3& color);
            Slider& setBackgroundColor(const glm::vec4& color);
            Slider& setAlpha(float alpha);
            Slider& setBackgroundAlpha(float alpha);
            Slider& setRange(float min, float max);
            Slider& setMin(float min);
            Slider& setMax(float max);
            Slider& setValue(float progress);
            Slider& setSize(const glm::vec2& size);
            Slider& setPosition(const glm::vec2& position);
            Slider& setPosition(const GLUL::Point& position);

            Slider& restrictValuesToIntegers(bool value);
            Slider& restrictValuesTo(std::initializer_list<float> values);

            Style::Border border;

        private:
            void clampValue();
            std::vector<glm::vec4> getVertices() const;

            void initializeEvents();

            bool isMoving() const;
            void setMovingState(bool value);
            void updateValueFromPosition(const glm::vec2& position);

            bool _isMoving;
            bool _glInitialized;
            bool _integerRestriction;
            float _rangeMin;
            float _rangeMax;
            float _currentValue;;
            std::vector<float> _possibleValues;
            glm::vec4 _color;
            glm::vec4 _backgroundColor;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;

        private:
            static GL::Program& getProgram();
        };

    }

}
