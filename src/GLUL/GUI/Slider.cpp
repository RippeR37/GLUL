#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Slider.h>
#include <GLUL/Logger.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        Slider::Slider(Container& parent, float min, float max, float value) 
            : Slider(&parent, min, max, value) { }

        Slider::Slider(Container* const parent, float min, float max, float value) 
            : Component(parent), border(*this) 
        {
            setColor(glm::vec4(glm::vec3(1.0f), 1.0f));
            setBackgroundColor(glm::vec4(glm::vec3(0.0f), 1.0f));
            restrictValuesToIntegers(false);
            setRange(min, max);
            setValue(value);
            setMovingState(false);

            initializeEvents();

            _glInitialized = false;
        }

        Slider::~Slider() {

        }

        const Slider& Slider::render() const {
            if(isVisible() && getAlpha() > 0.0f && getBackgroundAlpha() > 0.0f) {
                if(!isValid())
                    validate();

                getProgram().use();

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

                getProgram().unbind();
            }

            return *this;
        }

        Slider& Slider::update(double deltaTime) {
            if(!isValid())
                validate();

            (void)deltaTime; // unused

            return *this;
        }

        const Slider& Slider::validate() const {
            Slider* thisConstless = const_cast<Slider*>(this);

            // (Re)build VBO
            GL::VertexBuffer::Data vertexData;
            std::vector<glm::vec4> vertices = getVertices();

            vertexData.data = vertices.data();
            vertexData.size = vertices.size() * sizeof(glm::vec4);
            vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, sizeof(glm::vec4) + sizeof(glm::vec4), nullptr));
            vertexData.pointers.push_back(GL::VertexAttrib(1, 4, GL_FLOAT, sizeof(glm::vec4) + sizeof(glm::vec4), (GLvoid*)sizeof(glm::vec4)));

            _vbo.bind();
            thisConstless->_vbo.setUsage(GL::VertexBuffer::Usage::DynamicDraw);
            thisConstless->_vbo.setData(vertexData);
            _vbo.unbind();

            // Initialize VAO
            if(_glInitialized == false) {
                thisConstless->_vao.setDrawCount(vertices.size());
                thisConstless->_vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);

                _vao.bind();
                thisConstless->_vao.attachVBO(&_vbo);
                thisConstless->_vao.setAttribPointers();
                _vao.unbind();

                thisConstless->_glInitialized = true;
            }

            thisConstless->setValid();

            return *this;
        }


        const glm::vec4& Slider::getColor() const {
            return _color;
        }

        const glm::vec4& Slider::getBackgroundColor() const {
            return _backgroundColor;
        }

        float Slider::getAlpha() const {
            return getColor().a;
        }

        float Slider::getBackgroundAlpha() const {
            return getBackgroundColor().a;
        }

        float Slider::getValue() const {
            return _currentValue;
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


        Slider& Slider::setColor(const glm::vec3& color) {
            return setColor(glm::vec4(color, getAlpha()));
        }

        Slider& Slider::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();

            return *this;
        }

        Slider& Slider::setBackgroundColor(const glm::vec3& color) {
            return setBackgroundColor(glm::vec4(color, getBackgroundAlpha()));
        }

        Slider& Slider::setBackgroundColor(const glm::vec4& color) {
            _backgroundColor = color;

            setInvalid();

            return *this;
        }

        Slider& Slider::setAlpha(float alpha) {
            glm::vec4 color = getColor();

            color.a = alpha;

            return setColor(color);
        }

        Slider& Slider::setBackgroundAlpha(float alpha) {
            glm::vec4 backgroundColor = getBackgroundColor();

            backgroundColor.a = alpha;

            return setBackgroundColor(backgroundColor);
        }

        Slider& Slider::setRange(float min, float max) {
            _rangeMin = min;
            _rangeMax = max;
            std::vector<float>().swap(_possibleValues);

            clampValue();

            return *this;
        }

        Slider& Slider::setMin(float min) {
            return setRange(min, getMax());
        }

        Slider& Slider::setMax(float max) {
            return setRange(getMin(), max);
        }

        Slider& Slider::setValue(float value) {
            if(_possibleValues.empty()) {
                _currentValue = value;
                clampValue();

            } else {
                float currentBest = _possibleValues.front();
                float currentDist = std::abs(value - currentBest);

                for(float possibleValue : _possibleValues) {
                    if(std::abs(possibleValue - value) < currentDist) {
                        currentBest = possibleValue;
                        currentDist = std::abs(possibleValue - value);
                    }
                }

                _currentValue = currentBest;
            }

            setInvalid();

            return *this;
        }

        Slider& Slider::setSize(const glm::vec2& size) {
            Component::setSize(size);

            return *this;
        }

        Slider& Slider::setPosition(const glm::vec2& position) {
            Component::setPosition(position);

            return *this;
        }

        Slider& Slider::setPosition(const GLUL::Point& position) {
            Component::setPosition(position);

            return *this;
        }


        Slider& Slider::restrictValuesToIntegers(bool value) {
            _integerRestriction = value;
            clampValue();

            return *this;
        }

        Slider& Slider::restrictValuesTo(std::initializer_list<float> values) {
            std::vector<float>().swap(_possibleValues);
            _possibleValues.reserve(values.size());

            std::copy(std::begin(values), std::end(values), std::begin(_possibleValues));
            std::sort(std::begin(_possibleValues), std::end(_possibleValues));

            setRange(_possibleValues.front(), _possibleValues.back());
            setValue(getValue());

            return *this;
        }


        void Slider::clampValue() {
            _currentValue = std::min(_rangeMax, std::max(_rangeMin, _currentValue));

            if(_integerRestriction)
                _currentValue = std::round(_currentValue);

            if(_currentValue < _rangeMin) _currentValue += 1.0f;
            if(_currentValue > _rangeMax) _currentValue -= 1.0f;

            setInvalid();
        }

        GL::Program& Slider::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
                );

            return program;
        }

        std::vector<glm::vec4> Slider::getVertices() const {
            std::vector<glm::vec4> result;

            const float lineHeight = getSize().y / 15.0f;
            const float handleWidth = getSize().y / 3.0f;
            const float handleRange = getSize().x - handleWidth;

            glm::vec2 scrPos = getScreenPosition().getPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posEnd  = posStart + glm::vec2(getSize().x, -getSize().y);

            glm::vec2 posStartLine = glm::vec2(posStart.x, posStart.y - getSize().y * 0.5f - lineHeight * 0.5f);
            glm::vec2 posEndLine = glm::vec2(posEnd.x, posStartLine.y + lineHeight);

            glm::vec2 posStartHandle = glm::vec2(posStart.x + handleRange * normalizeValue(getValue()), posStart.y);
            glm::vec2 posEndHandle = glm::vec2(posStartHandle.x + handleWidth, posEnd.y);

            glm::vec2 borStart = posStart - glm::vec2(border.getOffset(), -border.getOffset());
            glm::vec2 borEnd = posEnd - glm::vec2(-border.getOffset(), border.getOffset());
            glm::vec2 borWidth = glm::vec2(static_cast<float>(border.getWidth()));

            static auto addRectangleVerticesWithColor =
                [](
                std::vector<glm::vec4>& result,
                const glm::vec2& posStart,
                const glm::vec2& posEnd,
                const glm::vec4& color
                )
            {
                // Vertices                                                     // Colors
                result.emplace_back(posStart.x, posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);

                result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
            };

            // Background
            if(getBackgroundAlpha() > 0.0f)
                addRectangleVerticesWithColor(result, posStart, posEnd, getBackgroundColor());

            if(getAlpha() > 0.0f) {
                // Horizontal line
                addRectangleVerticesWithColor(result, posStartLine, posEndLine, getColor() * 0.75f);

                // Slider's handle
                addRectangleVerticesWithColor(result, posStartHandle, posEndHandle, getColor());
            }

            // Border
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borEnd.x, borStart.y - borWidth.y), border.getColor()); // top
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borStart.x + borWidth.x, borEnd.y), border.getColor()); // left
            addRectangleVerticesWithColor(result, glm::vec2(borEnd.x - borWidth.x, borStart.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // right
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borEnd.y + borWidth.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // bottom

            return result;
        }

        void Slider::initializeEvents() {
            // Move to point where you clicked
            onMouseClick += GLUL::GUI::Event::MouseClick::Handler(
                "__GLUL::GUI::Slider::MouseClick::Move",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseClickEvent.button == GLUL::Input::MouseButton::Left)
                        slider.updateValueFromPosition(mouseClickEvent.position);
                }
            );

            // Set slider's handle state to being dragged
            onMouseClick += GLUL::GUI::Event::MouseClick::Handler(
                "__GLUL::GUI::Slider::MouseClick::SetMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseClickEvent.button == GLUL::Input::MouseButton::Left)
                        slider.setMovingState(true);
                }
            );

            // Set slider's handle state to being released
            onMouseRelease += GLUL::GUI::Event::MouseRelease::Handler(
                "__GLUL::GUI::Slider::MouseRelease::SetNotMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseRelease& mouseReleaseEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(mouseReleaseEvent.button == GLUL::Input::MouseButton::Left)
                        slider.setMovingState(false);
                }
            );

            // Set slider's handle state to being released
            onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
                "__GLUL::GUI::Slider::MouseLeave::SetNotMoving",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseLeaveEvent) {
                    (void) mouseLeaveEvent; // unused

                    Slider& slider = static_cast<Slider&>(component);
                    slider.setMovingState(false);
                }
            );

            onMouseMove += GLUL::GUI::Event::MouseMove::Handler(
                "__GLUL::GUI::Slider::MouseMove::UpdateValue",
                [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseMove& mouseMoveEvent) {
                    Slider& slider = static_cast<Slider&>(component);

                    if(slider.isMoving())
                        slider.updateValueFromPosition(mouseMoveEvent.position);
                }
            );
        }

        bool Slider::isMoving() const {
            return _isMoving;
        }

        void Slider::setMovingState(bool value) {
            _isMoving = value;
        }

        void Slider::updateValueFromPosition(const glm::vec2& position) {
            const float handleWidth = getSize().y / 3.0f;
            const float sliderWidth = getSize().x - handleWidth;
            const float normalizedNewValue = (position.x - 0.5f * handleWidth) / sliderWidth;
            const float denormalizedNewValue = denormalizeValue(normalizedNewValue);

            setValue(denormalizedNewValue);

            //std::cout << "Aktualizuje wartosc:"
        }

    }

}
