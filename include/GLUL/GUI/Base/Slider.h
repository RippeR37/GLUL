#pragma once

#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Slider : public Component {
                public:
                    virtual ~Slider() = default;

                    operator float() const;

                    virtual float getValue() const;
                    virtual float getMin() const;
                    virtual float getMax() const;
                    virtual float normalizeValue(float value) const;
                    virtual float denormalizeValue(float normalizedValue) const;

                    virtual void setRange(float min, float max);
                    virtual void setMin(float min);
                    virtual void setMax(float max);
                    virtual void setValue(float progress);
                    virtual void setSize(const glm::vec2& size);
                    virtual void restrictValuesToIntegers(bool value);
                    virtual void restrictValuesTo(std::initializer_list<float> values);

                    Event::HandlerAggregator<Event::ValueChange<float>> onValueChange;

                protected:
                    Slider(const Container& parent, float min, float max, float value);
                    Slider(const Container& parent, const glm::vec2& size, const glm::vec2& position,
                        float min, float max, float value);

                    void _initializeHandlers();
                    void _clampValue();
                    bool _isMoving() const;
                    void _setMovingState(bool value);
                    virtual void _updateValueFromPosition(const glm::vec2& position);

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

}
