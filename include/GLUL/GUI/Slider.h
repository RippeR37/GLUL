#pragma once

#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API Slider : public Component {
            public:
                operator float() const;

                float getValue() const;
                float getMin() const;
                float getMax() const;
                float normalizeValue(float value) const;
                float denormalizeValue(float normalizedValue) const;

                void setRange(float min, float max);
                void setMin(float min);
                void setMax(float max);
                void setValue(float progress);
                void setSize(const glm::vec2& size);
                void restrictValuesToIntegers(bool value);
                void restrictValuesTo(std::initializer_list<float> values);

                Event::HandlerAggregator<Event::ValueChange<float>> onValueChange;

            protected:
                Slider(const Container& parent, float min = 0.0f, float max = 1.0f, float value = 0.0f);
                Slider(const Container& parent, const glm::vec2& size, const glm::vec2& position,
                    float min = 0.0f, float max = 1.0f, float value = 0.0f);

                void _initializeHandlers();
                void _clampValue();
                bool _isMoving() const;
                void _setMovingState(bool value);
                void _updateValueFromPosition(const glm::vec2& position);
                void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                bool _isMovingState;
                bool _isIntegerRestricted;
                float _rangeMin;
                float _rangeMax;
                float _value;
                std::vector<float> _possibleValues;

                friend class Container;
        };

    }

}
