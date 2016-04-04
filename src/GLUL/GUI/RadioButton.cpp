#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/RadioButton.h>
#include <GLUL/GUI/RadioButtonGroup.h>
#include <GLUL/Logger.h>


namespace GLUL {

    namespace GUI {

        RadioButton::RadioButton(RadioButtonGroup& group, Container& parent, bool state) 
            : RadioButton(group, &parent, state) { }

        RadioButton::RadioButton(RadioButtonGroup& group, Container* const parent, bool state) 
            : Component(parent), border(*this), _group(group)
        {
            setColor(glm::vec4(1.0f));
            setMarkColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            setMarkScale(0.5f);
            setState(state);

            _glInitialized = false;

            onMouseClick += Event::MouseClick::Handler(
                "__GLUL::GUI::RadioButton::MouseClick",
                [](Component& component, const Event::MouseClick& onMouseClickEvent) {
                    RadioButton& radioButton = *static_cast<RadioButton*>(&component);

                    if(onMouseClickEvent.button == Input::MouseButton::Left)
                        radioButton._group.set(radioButton);
                }
            );
        }

        RadioButton::~RadioButton() {

        }

        RadioButton::operator bool() const {
            return getState();
        }

        const RadioButton& RadioButton::render() const {
            if(isVisible() && getAlpha() > 0.0f) {
                if(!isValid())
                    validate();

                // Render using font
                getProgram().use();

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

                getProgram().unbind();
            }

            return *this;
        }

        RadioButton& RadioButton::update(double deltaTime) {
            (void)deltaTime;

            if(!isValid())
                validate();

            return *this;
        }

        const RadioButton& RadioButton::validate() const {
            RadioButton* thisConstless = const_cast<RadioButton*>(this);

            // (Re)build VBO
            GL::VertexBuffer::Data vertexData;
            std::vector<glm::vec4> vertices = getVertices();

            vertexData.data = vertices.data();
            vertexData.size = vertices.size() * sizeof(glm::vec4);
            vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, sizeof(glm::vec4) * 2, nullptr));
            vertexData.pointers.push_back(GL::VertexAttrib(1, 4, GL_FLOAT, sizeof(glm::vec4) * 2, sizeof(glm::vec4)));

            _vbo.bind();
                thisConstless->_vbo.setUsage(GL::VertexBuffer::Usage::DynamicDraw);
                thisConstless->_vbo.setData(vertexData);
            _vbo.unbind();

            // Set vertices draw count
            thisConstless->_vao.setDrawCount(vertices.size() / 2);

            // Initialize VAO
            if(_glInitialized == false) {
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

        const glm::vec4& RadioButton::getColor() const {
            return _color;
        }

        const glm::vec4& RadioButton::getMarkColor() const {
            return _markColor;
        }

        float RadioButton::getMarkScale() const {
            return _markScale;
        }

        float RadioButton::getAlpha() const {
            return _color.a;
        }

        bool RadioButton::getState() const {
            return _state;
        }

        RadioButton& RadioButton::set() {
            _group.set(*this);

            return *this;
        }

        RadioButton& RadioButton::setColor(const glm::vec3& color) {
            setColor(glm::vec4(color, getAlpha()));

            return *this;
        }

        RadioButton& RadioButton::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();

            return *this;
        }

        RadioButton& RadioButton::setMarkColor(const glm::vec3& color) {
            setMarkColor(glm::vec4(color, getMarkColor().a));

            return *this;
        }

        RadioButton& RadioButton::setMarkColor(const glm::vec4& color) {
            _markColor = color;

            setInvalid();

            return *this;
        }

        RadioButton& RadioButton::setMarkScale(float scale) {
            _markScale = scale;

            setInvalid();

            return *this;
        }

        RadioButton& RadioButton::setAlpha(float alpha) {
            setColor(glm::vec4(getColor().r, getColor().g, getColor().b, alpha));

            return *this;
        }

        RadioButton& RadioButton::setSize(const glm::vec2& size) {
            Component::setSize(size);

            return *this;
        }

        RadioButton& RadioButton::setPosition(const glm::vec2& position) {
            Component::setPosition(position);

            return *this;
        }

        RadioButton& RadioButton::setPosition(const GLUL::Point& position) {
            Component::setPosition(position);

            return *this;
        }


        GL::Program& RadioButton::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
            );

            return program;
        }

        RadioButton& RadioButton::setState(bool state) {
            bool oldState = getState();

            _state = state;

            setInvalid();
            validate();

            onValueChange.call(*this, GLUL::GUI::Event::ValueChange<bool>(oldState, getState()));

            return *this;
        }

        std::vector<glm::vec4> RadioButton::getVertices() const {
            std::vector<glm::vec4> result;

            glm::vec2 scrPos = getScreenPosition().getPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posCenter = posStart + glm::vec2(getSize().x, -getSize().y) * 0.5f;

            // Radio button
            float radius = getSize().x * 0.5f;
            pushColoredDisk(result, posCenter, radius, getColor());

            // Radio button's mark
            if(getState() == true) {
                float markRadius = radius * getMarkScale();

                pushColoredDisk(result, posCenter, markRadius, getMarkColor());
            }

            // Border
            if(border.getWidth() > 0) {
                // TODO:
            }

            return result;
        }

    }

}
