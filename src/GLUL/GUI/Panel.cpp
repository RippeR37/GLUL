#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Panel.h>
#include <GLUL/GUI/Events/ValueChange.hpp>

#include <iostream>


namespace GLUL {

    namespace GUI {

        Panel::Panel(Container& parent, const glm::vec2& position, const glm::vec2& size)
            : Panel(&parent, position, size) { }

        Panel::Panel(Container& parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& totalSize)
            : Panel(&parent, position, size, totalSize) { }

        Panel::Panel(Container* const parent, const glm::vec2& position, const glm::vec2& size)
            : Panel(parent, position, size, size) { }

        Panel::Panel(Container* const parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& totalSize)
            : Container(nullptr), _glInitialized(false)
        {
            _initializeScrollbars();

            bindTo(parent);
            setSize(size);
            setPosition(position);
            setTotalSize(totalSize);
            setBackgroundColor({ 0.0f, 0.0f, 0.0f, 0.1f });
        }

        Panel::~Panel() {
            bindTo(nullptr);
        }


        void Panel::bindTo(Container& container) {
            bindTo(&container);
        }

        void Panel::bindTo(Container* container) {
            Container::bindTo(container);

            scrollbarHorizontal.bindTo(container);
            scrollbarVertical.bindTo(container);
        }

        
        const Panel& Panel::render() const {
            if(isVisible()) {
                if(!isValid())
                    validate();

                getProgram().use();

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

                getProgram().unbind();
            }

            Container::render();

            return *this;
        }

        Panel& Panel::update(double deltaTime) {
            if(!isValid())
                validate();

            Container::update(deltaTime);

            return *this;
        }

        const Panel& Panel::validate() const {
            Panel* thisConstless = const_cast<Panel*>(this);

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

        const glm::vec2 Panel::getScreenPosition() const {
            glm::vec2 scrPos = Container::getScreenPosition();
            glm::vec2 offset = getOffset();

            return scrPos - offset;
        }

        const glm::vec2 Panel::getOffset() const {
            return {
                scrollbarHorizontal.getValue(),
                scrollbarVertical.getMax() - scrollbarVertical.getValue()
            };
        }

        const glm::vec2& Panel::getTotalSize() const {
            return _totalSize;
        }

        const glm::vec4& Panel::getBackgroundColor() const {
            return _backgroundColor;
        }

        bool Panel::isHorizontalScrollbarVisible() const {
            return (getSize().x < getTotalSize().x);
        }

        bool Panel::isVerticalScrollbarVisible() const {
            return (getSize().y < getTotalSize().y);
        }

        Panel& Panel::setSize(const glm::vec2& size) {
            Container::setSize(size);

            _updateScrollbarLogic();

            return *this;
        }

        Panel& Panel::setTotalSize(const glm::vec2& totalSize) {
            _totalSize = totalSize;

            setInvalid();
            validate();
            _updateScrollbarLogic();

            return *this;
        }

        Panel& Panel::setPosition(const glm::vec2& position) {
            Container::setPosition(position);

            _updateScrollbarLogic();

            return *this;
        }

        Panel& Panel::setBackgroundColor(const glm::vec3& backgroundColor) {
            return setBackgroundColor(glm::vec4(backgroundColor, 1.0f));
        }

        Panel& Panel::setBackgroundColor(const glm::vec4& backgroundColor) {
            _backgroundColor = backgroundColor;

            setInvalid();

            return *this;
        }


        void Panel::_initializeScrollbars() {
            scrollbarHorizontal.setOrientation(Style::Orientation::Horizontal);
            scrollbarVertical.setOrientation(Style::Orientation::Vertical);

            scrollbarHorizontal.onValueChange += Event::ValueChange<float>::Handler(
                "__GLUL::GUI::Panel::HorizontalScrollbar::ValueChange",
                [&](Component& component, const Event::ValueChange<float>& onValueChangeEvent) {
                    (void) component;
                    (void) onValueChangeEvent;

                    this->setInvalid();
                }
            );

            scrollbarVertical.onValueChange += Event::ValueChange<float>::Handler(
                "__GLUL::GUI::Panel::VerticalScrollbar::ValueChange",
                [&](Component& component, const Event::ValueChange<float>& onValueChangeEvent) {
                    (void) component;
                    (void) onValueChangeEvent;

                    this->setInvalid();
                }
            );
        }

        void Panel::_updateScrollbarLogic() {
            scrollbarHorizontal.setEnabled(isHorizontalScrollbarVisible());
            scrollbarHorizontal.setVisible(isHorizontalScrollbarVisible());
            scrollbarVertical.setEnabled(isVerticalScrollbarVisible());
            scrollbarVertical.setVisible(isVerticalScrollbarVisible());

            glm::vec2 pos = getPosition();

            // Horizontal scrollbar
            if(isHorizontalScrollbarVisible()) {
                scrollbarHorizontal.setRange(0.0f, getTotalSize().x - getSize().x);
                scrollbarHorizontal.setSize({ getSize().x - 10.0f, 10.0f });
                scrollbarHorizontal.setPosition(pos + glm::vec2(0.0f, getSize().y - 10.0f));
            }

            // Vertical scrollbar
            if(isVerticalScrollbarVisible()) {
                scrollbarVertical.setRange(0.0f, getTotalSize().y - getSize().y);
                scrollbarVertical.setValue(scrollbarVertical.getMax());
                scrollbarVertical.setSize({ 10.0f, getSize().y - 10.0f });
                scrollbarVertical.setPosition(pos + glm::vec2(getSize().x - 10.0f, 0.0f));
            }
        }

        GL::Program& Panel::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
            );

            return program;
        }

        std::vector<glm::vec4> Panel::getVertices() const {
            std::vector<glm::vec4> result;

            // Background position
            glm::vec2 scrPos = Container::getScreenPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posEnd = posStart + glm::vec2(getSize().x, -getSize().y);

            // Push vertices to vector
            pushColoredRectangle(result, posStart, posEnd, _backgroundColor);

            return result;
        }

    }

}
