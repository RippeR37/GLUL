#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/Checkbox.h>
#include <GLUL/Logger.h>

#include <cctype>


namespace GLUL {

    namespace GUI {

        Checkbox::Checkbox(Container& parent, bool state) : Checkbox(&parent, state) {

        }

        Checkbox::Checkbox(Container* const parent, bool state) : Component(parent), border(*this) {
            setColor(glm::vec4(1.0f));
            setMarkColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            setMarkScale(0.5f);
            setState(state);

            _glInitialized = false;

            onMouseClick += Event::MouseClick::Handler(
                "__GLUL::GUI::Checkbox::MouseClick",
                [&](Component& component, const Event::MouseClick& onMouseClickEvent) {
                    (void) onMouseClickEvent;
                    Checkbox& checkbox = *static_cast<Checkbox*>(&component);

                    checkbox.switchState();
                }
            );
        }

        Checkbox::~Checkbox() {

        }
        
        Checkbox::operator bool() const {
            return getState();
        }

        void Checkbox::render() const {
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
        }

        void Checkbox::update(double deltaTime) {
            (void) deltaTime;

            if(!isValid())
                validate();
        }

        void Checkbox::validate() const {
            Checkbox* thisConstless = const_cast<Checkbox*>(this);

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
        }

        const glm::vec4& Checkbox::getColor() const {
            return _color;
        }

        const glm::vec4& Checkbox::getMarkColor() const {
            return _markColor;
        }

        float Checkbox::getMarkScale() const {
            return _markScale;
        }

        float Checkbox::getAlpha() const {
            return _color.a;
        }

        bool Checkbox::getState() const {
            return _state;
        }

        void Checkbox::setColor(const glm::vec3& color) {
            setColor(glm::vec4(color, getAlpha()));
        }

        void Checkbox::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();
        }

        void Checkbox::setMarkColor(const glm::vec3& color) {
            setMarkColor(glm::vec4(color, getMarkColor().a));
        }

        void Checkbox::setMarkColor(const glm::vec4& color) {
            _markColor = color;

            setInvalid();
        }

        void Checkbox::setMarkScale(float scale) {
            _markScale = scale;

            setInvalid();
        }

        void Checkbox::setAlpha(float alpha) {
            setColor(glm::vec4(getColor().r, getColor().g, getColor().b, alpha));
        }

        void Checkbox::setState(bool state) {
            _state = state;

            setInvalid();
            validate();
        }

        bool Checkbox::switchState() {
            setState(!getState());

            return getState();
        }

        GL::Program& Checkbox::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader), 
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
            );

            return program;
        }

        std::vector<glm::vec4> Checkbox::getVertices() const {
            std::vector<glm::vec4> result;

            glm::vec2 scrPos = getScreenPosition().getPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posEnd = posStart + glm::vec2(getSize().x, -getSize().y);

            glm::vec2 borStart = posStart - glm::vec2( border.getOffset(), -border.getOffset());
            glm::vec2 borEnd   = posEnd   - glm::vec2(-border.getOffset(),  border.getOffset());
            glm::vec2 borWidth = glm::vec2(static_cast<float>(border.getWidth()));

            static auto addRectangleVerticesWithColor = [](std::vector<glm::vec4>& result, const glm::vec2& posStart, const glm::vec2& posEnd, const glm::vec4& color) 
            {
                // Vertices                                                     // Colors
                result.emplace_back(posStart.x, posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);

                result.emplace_back(posStart.x, posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posStart.y, 0.0f, 1.0f);        result.emplace_back(color);
                result.emplace_back(posEnd.x,   posEnd.y,   0.0f, 1.0f);        result.emplace_back(color);
            };

            // Button
            addRectangleVerticesWithColor(result, posStart, posEnd, getColor());

            if(getState() == true) {
                glm::vec2 markDiff = glm::vec2(
                     0.5f * getMarkScale() * getSize().x, 
                    -0.5f * getMarkScale() * getSize().y
                );

                addRectangleVerticesWithColor(result, posStart + markDiff, posEnd - markDiff, getMarkColor());
            }

            // Border
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borEnd.x, borStart.y - borWidth.y), border.getColor()); // top
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borStart.x + borWidth.x, borEnd.y), border.getColor()); // left
            addRectangleVerticesWithColor(result, glm::vec2(borEnd.x   - borWidth.x, borStart.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // right
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borEnd.y + borWidth.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // bottom

            return result;
        }

    }

}
