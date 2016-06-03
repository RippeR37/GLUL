#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Slider.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        Slider::Slider(const Container& parent, float min, float max, float value)
            : Slider(parent, {}, {}, min, max, value) { }

        Slider::Slider(const Container& parent, const glm::vec2& size, const glm::vec2& position, float min, float max, float value)
            : Component(parent, size, position), _rangeMin(min), _rangeMax(max), _value(value)
        {
            _initializeHandlers();
        }

        float Slider::getValue() const {
            return _value;
        }

        float Slider::getMin() const {
            if(_possibleValues.empty())
                return _rangeMin;
            else
                return _possibleValues.front();
        }

        float Slider::getMax() const {
            if(_possibleValues.empty())
                return _rangeMax;
            else
                return _possibleValues.back();
        }

        float Slider::normalizeValue(float value) const {
            return (value - getMin()) / (getMax() - getMin());
        }

        float Slider::denormalizeValue(float normalizedValue) const {
            return getMin() + (getMax() - getMin()) * normalizedValue;
        }

        void Slider::setRange(float min, float max) {
            _rangeMin = min;
            _rangeMax = max;

            // clear vector of possible values
            std::vector<float>().swap(_possibleValues);

            _clampValue();
        }

        void Slider::setMin(float min) {
            setRange(min, getMax());
        }

        void Slider::setMax(float max) {
            setRange(getMin(), max);
        }

        void Slider::setValue(float value) {
            float oldValue = getValue();

            if(_possibleValues.empty()) {
                _value = value;
                _clampValue();

            } else {
                float currentBest = _possibleValues.front();
                float currentDist = std::abs(value - currentBest);

                // TODO: optimize this with std::lower_bound
                for(float possibleValue : _possibleValues) {
                    if(std::abs(possibleValue - value) < currentDist) {
                        currentBest = possibleValue;
                        currentDist = std::abs(possibleValue - value);
                    }
                }

                _value = currentBest;
            }

            setInvalid();

            onValueChange.call(*this, GLUL::GUI::Event::ValueChange<float>(oldValue, getValue()));
        }

        void Slider::setSize(const glm::vec2& size) {
            Component::setSize(size);

            // Orientation-dependent settings?
        }

        void Slider::restrictValuesToIntegers(bool value) {
            _isIntegerRestricted = value;
            _clampValue();

            setInvalid();
        }

        void Slider::restrictValuesTo(std::initializer_list<float> values) {
            _possibleValues = std::vector<float>(values.size());

            std::copy(std::begin(values), std::end(values), std::begin(_possibleValues));
            std::sort(std::begin(_possibleValues), std::end(_possibleValues));

            setRange(_possibleValues.front(), _possibleValues.back());
            setValue(getValue());
        }

        void Slider::_clampValue() {
            _value = std::min(_rangeMax, std::max(_rangeMin, _value));

            if(_isIntegerRestricted)
                _value = std::round(_value);

            if(_value < _rangeMin) _value += 1.0f;
            if(_value > _rangeMax) _value -= 1.0f;

            setInvalid();
        }

        void Slider::_initializeHandlers() {
            // Move to point where you clicked
            onMouseClick += GLUL::GUI::Event::MouseClick::Handler(
                "__GLUL::GUI::Slider::MouseClick::Move",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseClickEvent.button == GLUL::Input::MouseButton::Left)
                        slider._updateValueFromPosition(mouseClickEvent.position);
                }
            );

            // Set slider's handle state to being dragged
            onMouseClick += GLUL::GUI::Event::MouseClick::Handler(
                "__GLUL::GUI::Slider::MouseClick::SetMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseClickEvent.button == GLUL::Input::MouseButton::Left)
                        slider._setMovingState(true);
                }
            );

            // Set slider's handle state to being released
            onMouseRelease += GLUL::GUI::Event::MouseRelease::Handler(
                "__GLUL::GUI::Slider::MouseRelease::SetNotMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseRelease& mouseReleaseEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseReleaseEvent.button == GLUL::Input::MouseButton::Left)
                        slider._setMovingState(false);
                }
            );

            // Set slider's handle state to being released
            onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
                "__GLUL::GUI::Slider::MouseLeave::SetNotMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseLeaveEvent) {
                    (void) mouseLeaveEvent; // unused

                    Slider& slider = static_cast<Slider&>(component);
                    slider._setMovingState(false);
                }
            );

            onMouseMove += GLUL::GUI::Event::MouseMove::Handler(
                "__GLUL::GUI::Slider::MouseMove::UpdateValue",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseMove& mouseMoveEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(slider._isMoving())
                        slider._updateValueFromPosition(mouseMoveEvent.position);
                }
            );
        }

        bool Slider::_isMoving() const {
            return _isMovingState;
        }

        void Slider::_setMovingState(bool value) {
            _isMovingState = value;
        }

        void Slider::_updateValueFromPosition(const glm::vec2& position) {
            (void) position;
            // TODO:

            /*
            float normalizedNewValue;
            if(getOrientation() == Style::Orientation::Horizontal) {
                float handleWidth = getHandleSize().x;
                float sliderRange = getSize().x - handleWidth;
                normalizedNewValue = (position.x - 0.5f * handleWidth) / sliderRange;

            } else {
                float handleHeight = getHandleSize().y;
                float sliderRange = getSize().y - handleHeight;
                normalizedNewValue = 1.0f - ((position.y - 0.5f * handleHeight) / sliderRange); // inverted (bottom is min, top is max)
            }

            setValue(denormalizeValue(normalizedNewValue));
            */
        }

        void Slider::_pushToBatch(G2D::TexturedBatch& texBatch) const {
            (void) texBatch;
            // TODO:
        }

    }

}
