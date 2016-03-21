#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Button.h>
#include <GLUL/Logger.h>

#include <cctype>


namespace GLUL {

    namespace GUI {

        Button::Button(Container& parent) : Button(&parent) {

        }

        Button::Button(Container* const parent) : Component(parent), text(*this), border(*this) {
            setColor(glm::vec4(1.0f));

            _glInitialized = false;
        }

        Button::~Button() {

        }

        const Button& Button::render() const {
            if(isVisible() && getAlpha() > 0.0f) {
                if(!isValid())
                    validate();

                // Render using font
                getProgram().use();

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

                getProgram().unbind();

                text.render();
            }

            return *this;
        }

        Button& Button::update(double deltaTime) {
            if(!isValid())
                validate();

            text.update(deltaTime);

            return *this;
        }

        const Button& Button::validate() const {
            Button* thisConstless = const_cast<Button*>(this);

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

            // Update button's text position
            thisConstless->text.updatePosition();

            thisConstless->setValid();

            return *this;
        }

        const glm::vec4& Button::getColor() const {
            return _color;
        }

        float Button::getAlpha() const {
            return _color.a;
        }

        Button& Button::setColor(const glm::vec3& color) {
            setColor(glm::vec4(color, getAlpha()));

            return *this;
        }

        Button& Button::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();

            return *this;
        }

        Button& Button::setAlpha(const float alpha) {
            setColor(glm::vec4(getColor().r, getColor().g, getColor().b, alpha));

            return *this;
        }


        Button& Button::setSize(const glm::vec2& size) {
            Component::setSize(size);

            return *this;
        }

        Button& Button::setPosition(const glm::vec2& position) {
            Component::setPosition(position);

            return *this;
        }

        Button& Button::setPosition(const GLUL::Point& position) {
            Component::setPosition(position);

            return *this;
        }


        GL::Program& Button::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader), 
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
            );

            return program;
        }

        std::vector<glm::vec4> Button::getVertices() const {
            std::vector<glm::vec4> result;

            glm::vec2 scrPos = getScreenPosition().getPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posEnd = posStart + glm::vec2(getSize().x, -getSize().y);

            glm::vec2 borStart = posStart - glm::vec2( border.getOffset(), -border.getOffset());
            glm::vec2 borEnd   = posEnd   - glm::vec2(-border.getOffset(),  border.getOffset());
            glm::vec2 borWidth = glm::vec2(static_cast<float>(border.getWidth()));

            // Button
            pushColoredRectangle(result, posStart, posEnd, getColor());

            // Border
            pushColoredRectangle(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borEnd.x, borStart.y - borWidth.y), border.getColor()); // top
            pushColoredRectangle(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borStart.x + borWidth.x, borEnd.y), border.getColor()); // left
            pushColoredRectangle(result, glm::vec2(borEnd.x - borWidth.x, borStart.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // right
            pushColoredRectangle(result, glm::vec2(borStart.x, borEnd.y + borWidth.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // bottom

            return result;
        }

    }

}
