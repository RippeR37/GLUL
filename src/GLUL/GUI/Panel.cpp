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
            setScrollbarsSize({ 12.0f, 12.0f });
            setScrollbarsBackgroundColor({ 0.0f, 0.0f, 0.0f, 0.2f });
            setScrollbarsHandleColor({ 0.0f, 0.0f, 0.0f, 0.2f });
            setScrollbarsHandleSize({ 12.0f, 12.0f });
            setScrollbarsBorder(1, 0, { 0.0f, 0.0f, 0.0f });
            setScrollbarsHandleBorder(1, 0, { 0.0f, 0.0f, 0.0f });
        }

        Panel::~Panel() {
            bindTo(nullptr);
        }


        void Panel::bindTo(Container& container) {
            bindTo(&container);
        }

        void Panel::bindTo(Container* container) {
            Container::bindTo(container);

            _scrollbarHorizontal.bindTo(container);
            _scrollbarVertical.bindTo(container);
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
                _scrollbarHorizontal.getValue(),
                _scrollbarVertical.getMax() - _scrollbarVertical.getValue()
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

        const glm::vec2& Panel::getScrollbarsSize() const {
            return _scrollbarsSize;
        }

        const glm::vec2 Panel::getScrollbarsHandleSize() const {
            return _scrollbarHorizontal.getHandleSize();
        }

        const glm::vec2 Panel::getScrollbarsLineSize() const {
            return _scrollbarHorizontal.getLineSize();
        }

        const glm::vec4 Panel::getScrollbarsBackgroundColor() const {
            return _scrollbarHorizontal.getBackgroundColor();
        }

        const glm::vec4 Panel::getScrollbarsHandleColor() const {
            return _scrollbarHorizontal.getHandleColor();
        }

        const glm::vec4 Panel::getScrollbarsLineColor() const {
            return _scrollbarHorizontal.getLineColor();
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

        Panel& Panel::setScrollbarsSize(float scrollbarsSize) {
            return setScrollbarsSize({ scrollbarsSize, scrollbarsSize });
        }

        Panel& Panel::setScrollbarsSize(const glm::vec2& scrollbarsSize) {
            _scrollbarsSize = scrollbarsSize;

            _updateScrollbarLogic();

            return *this;
        }

        Panel& Panel::setScrollbarsBackgroundColor(const glm::vec3& scrollbarsBackgroundColor) {
            return setScrollbarsBackgroundColor(glm::vec4(scrollbarsBackgroundColor, 1.0f));
        }

        Panel& Panel::setScrollbarsBackgroundColor(const glm::vec4& scrollbarsBackgroundColor) {
            _scrollbarHorizontal.setBackgroundColor(scrollbarsBackgroundColor);
            _scrollbarVertical.setBackgroundColor(scrollbarsBackgroundColor);

            return *this;
        }

        Panel& Panel::setScrollbarsHandleSize(const glm::vec2& scrollbarsHandleSize) {
            _scrollbarHorizontal.setHandleSize(scrollbarsHandleSize);
            _scrollbarVertical.setHandleSize({ scrollbarsHandleSize.y, scrollbarsHandleSize.x });

            return *this;
        }

        Panel& Panel::setScrollbarsLineSize(const glm::vec2& scrollbarsLineSize) {
            _scrollbarHorizontal.setLineSize(scrollbarsLineSize);
            _scrollbarVertical.setLineSize({ scrollbarsLineSize.y, scrollbarsLineSize.x });

            return *this;
        }

        Panel& Panel::setScrollbarsHandleColor(const glm::vec3& scrollbarsHandleColor) {
            return setScrollbarsHandleColor(glm::vec4(scrollbarsHandleColor, 1.0f));
        }

        Panel& Panel::setScrollbarsHandleColor(const glm::vec4& scrollbarsHandleColor) {
            _scrollbarHorizontal.setHandleColor(scrollbarsHandleColor);
            _scrollbarVertical.setHandleColor(scrollbarsHandleColor);

            return *this;
        }

        Panel& Panel::setScrollbarsLineColor(const glm::vec3& scrollbarsLineColor) {
            return setScrollbarsLineColor(glm::vec4(scrollbarsLineColor, 1.0f));
        }

        Panel& Panel::setScrollbarsLineColor(const glm::vec4& scrollbarsLineColor) {
            _scrollbarHorizontal.setLineColor(scrollbarsLineColor);
            _scrollbarVertical.setLineColor(scrollbarsLineColor);

            return *this;
        }

        Panel& Panel::setScrollbarsBorder(int width, int offset, const glm::vec3& color) {
            return setScrollbarsBorder(width, offset, glm::vec4(color, 1.0f));
        }

        Panel& Panel::setScrollbarsBorder(int width, int offset, const glm::vec4& color) {
            _scrollbarHorizontal.border.set(width, offset, color);
            _scrollbarVertical.border.set(width, offset, color);

            return *this;
        }

        Panel& Panel::setScrollbarsHandleBorder(int width, int offset, const glm::vec3& color) {
            return setScrollbarsHandleBorder(width, offset, glm::vec4(color, 1.0f));
        }

        Panel& Panel::setScrollbarsHandleBorder(int width, int offset, const glm::vec4& color) {
            _scrollbarHorizontal.handleBorder.set(width, offset, color);
            _scrollbarVertical.handleBorder.set(width, offset, color);

            return *this;
        }


        void Panel::_initializeScrollbars() {
            _scrollbarHorizontal.setOrientation(Style::Orientation::Horizontal);
            _scrollbarVertical.setOrientation(Style::Orientation::Vertical);

            _scrollbarHorizontal.onValueChange += Event::ValueChange<float>::Handler(
                "__GLUL::GUI::Panel::HorizontalScrollbar::ValueChange",
                [&](Component& component, const Event::ValueChange<float>& onValueChangeEvent) {
                    (void) component;
                    (void) onValueChangeEvent;

                    this->setInvalid();
                }
            );

            _scrollbarVertical.onValueChange += Event::ValueChange<float>::Handler(
                "__GLUL::GUI::Panel::VerticalScrollbar::ValueChange",
                [&](Component& component, const Event::ValueChange<float>& onValueChangeEvent) {
                    (void) component;
                    (void) onValueChangeEvent;

                    this->setInvalid();
                }
            );
        }

        void Panel::_updateScrollbarLogic() {
            _scrollbarHorizontal.setEnabled(isHorizontalScrollbarVisible());
            _scrollbarHorizontal.setVisible(isHorizontalScrollbarVisible());
            _scrollbarVertical.setEnabled(isVerticalScrollbarVisible());
            _scrollbarVertical.setVisible(isVerticalScrollbarVisible());

            glm::vec2 pos = getPosition();

            // Horizontal scrollbar
            if(isHorizontalScrollbarVisible()) {
                _scrollbarHorizontal.setRange(0.0f, getTotalSize().x - getSize().x);
                _scrollbarHorizontal.setSize({ getSize().x - getScrollbarsSize().x, getScrollbarsSize().y });
                _scrollbarHorizontal.setPosition(pos + glm::vec2(0.0f, getSize().y - getScrollbarsSize().y ));
            }

            // Vertical scrollbar
            if(isVerticalScrollbarVisible()) {
                _scrollbarVertical.setRange(0.0f, getTotalSize().y - getSize().y);
                _scrollbarVertical.setValue(_scrollbarVertical.getMax());
                _scrollbarVertical.setSize({ getScrollbarsSize().x, getSize().y - getScrollbarsSize().y });
                _scrollbarVertical.setPosition(pos + glm::vec2(getSize().x - getScrollbarsSize().x, 0.0f));
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

            // Cube between scrollbars position
            glm::vec2 posCubeStart = posStart + glm::vec2(getSize().x, - getSize().y);
            glm::vec2 posCubeEnd = posCubeStart - glm::vec2(getScrollbarsSize().x, -getScrollbarsSize().y);

            // Background vertices
            pushColoredRectangle(result, posStart, posEnd, getBackgroundColor());

            // Small cube between horizontal and vertical scrollbars to fill void space
            pushColoredRectangle(result, posCubeStart, posCubeEnd, getScrollbarsBackgroundColor());

            return result;
        }

    }

}
