#include <GLUL/GL++/Context.h>
#include <GLUL/GUI/Container.h>
#include <GLUL/GUI/ProgressBar.h>
#include <GLUL/Logger.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        ProgressBar::ProgressBar(Container& parent, float progress) : ProgressBar(&parent, progress) {

        }

        ProgressBar::ProgressBar(Container* const parent, float progress) : Component(parent), border(*this) {
            setColor(glm::vec4(glm::vec3(1.0f), 1.0f));
            setBackgroundColor(glm::vec4(glm::vec3(0.0f), 1.0f));
            setProgress(progress);

            _glInitialized = false;
        }

        ProgressBar::~ProgressBar() {

        }

        const ProgressBar& ProgressBar::render() const {
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

        ProgressBar& ProgressBar::update(double deltaTime) {
            if(!isValid())
                validate();
            
            (void) deltaTime; // unused

            return *this;
        }

        const ProgressBar& ProgressBar::validate() const {
            ProgressBar* thisConstless = const_cast<ProgressBar*>(this);

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


        const glm::vec4& ProgressBar::getColor() const {
            return _color;
        }

        const glm::vec4& ProgressBar::getBackgroundColor() const {
            return _backgroundColor;
        }

        float ProgressBar::getAlpha() const {
            return getColor().a;
        }

        float ProgressBar::getBackgroundAlpha() const {
            return getBackgroundColor().a;
        }

        float ProgressBar::getProgress() const {
            return _progress;
        }


        ProgressBar& ProgressBar::setColor(const glm::vec3& color) {
            return setColor(glm::vec4(color, getAlpha()));
        }

        ProgressBar& ProgressBar::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();

            return *this;
        }

        ProgressBar& ProgressBar::setBackgroundColor(const glm::vec3& color) {
            return setBackgroundColor(glm::vec4(color, getBackgroundAlpha()));
        }

        ProgressBar& ProgressBar::setBackgroundColor(const glm::vec4& color) {
            _backgroundColor = color;

            setInvalid();

            return *this;
        }

        ProgressBar& ProgressBar::setAlpha(float alpha) {
            glm::vec4 color = getColor();
            
            color.a = alpha;
            
            return setColor(color);
        }

        ProgressBar& ProgressBar::setBackgroundAlpha(float alpha) {
            glm::vec4 backgroundColor = getBackgroundColor();

            backgroundColor.a = alpha;

            return setBackgroundColor(backgroundColor);
        }

        ProgressBar& ProgressBar::setProgress(float progress) {
            float oldProgress = getProgress();

            _progress = progress;

            setInvalid();

            onValueChange.call(*this, GLUL::GUI::Event::ValueChange<float>(oldProgress, getProgress()));

            return *this;
        }

        ProgressBar& ProgressBar::setSize(const glm::vec2& size) {
            Component::setSize(size);

            return *this;
        }

        ProgressBar& ProgressBar::setPosition(const glm::vec2& position) {
            Component::setPosition(position);

            return *this;
        }

        ProgressBar& ProgressBar::setPosition(const GLUL::Point& position) {
            Component::setPosition(position);

            return *this;
        }


        ProgressBar& ProgressBar::increaseProgress(float value) {
            return setProgress(std::min(getProgress() + value, 1.0f));
        }

        ProgressBar& ProgressBar::decreaseProgress(float value) {
            return setProgress(std::max(getProgress() - value, 0.0f));
        }


        GL::Program& ProgressBar::getProgram() {
            static GL::Program program(
                GL::Shader("assets/shaders/GLUL/GUI/Button.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/GUI/Button.fp", GL::Shader::Type::FragmentShader)
                );

            return program;
        }

        std::vector<glm::vec4> ProgressBar::getVertices() const {
            std::vector<glm::vec4> result;

            glm::vec2 scrPos = getScreenPosition().getPosition();
            glm::vec2 posStart = glm::vec2(scrPos.x, GL::Context::Current->getViewportSize().y - scrPos.y);
            glm::vec2 posEnd = posStart + glm::vec2(getSize().x, -getSize().y);
            glm::vec2 posEndBar = posStart + glm::vec2(getSize().x * getProgress(), -getSize().y);

            glm::vec2 borStart = posStart - glm::vec2(border.getOffset(), -border.getOffset());
            glm::vec2 borEnd = posEnd - glm::vec2(-border.getOffset(), border.getOffset());
            glm::vec2 borWidth = glm::vec2(static_cast<float>(border.getWidth()));

            // Background
            if(getBackgroundAlpha() > 0.0f)
                pushColoredRectangle(result, posStart, posEnd, getBackgroundColor());

            // ProgressBar
            if(getAlpha() > 0.0f && getProgress() > 0.0f)
                pushColoredRectangle(result, posStart, posEndBar, getColor());

            // Border
            pushColoredRectangle(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borEnd.x, borStart.y - borWidth.y), border.getColor()); // top
            pushColoredRectangle(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borStart.x + borWidth.x, borEnd.y), border.getColor()); // left
            pushColoredRectangle(result, glm::vec2(borEnd.x - borWidth.x, borStart.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // right
            pushColoredRectangle(result, glm::vec2(borStart.x, borEnd.y + borWidth.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // bottom

            return result;
        }

    }

}
