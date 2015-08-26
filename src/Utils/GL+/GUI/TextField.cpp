#include <Utils/GL+/GUI/Container.h>
#include <Utils/GL+/GUI/TextField.h>
#include <Utils/GL+/Context.h>
#include <Utils/Logger.h>

#include <cctype>


namespace GL {

    namespace GUI {

        TextField::TextField(Container& parent) : TextField(&parent) {

        }

        TextField::TextField(Container* const parent) : Component(parent), text(*this), border(*this) {
            setColor(glm::vec4(1.0f));

            onKeyStroke += Event::KeyStroke::Handler(
                "__UtilLib::GUI::TextField::KeyStroke", 
                [&](Component& component, const Event::KeyStroke& onKeyStrokeEvent) {
                    TextField& textField = *static_cast<TextField*>(&component);

                    int inputCharI = static_cast<int>(onKeyStrokeEvent.key);
                    char inputChar = static_cast<char>(inputCharI);
                    
                    if(std::isgraph(inputCharI) && inputCharI < 128 && inputCharI >= 0) {
                        textField.text.setText(textField.text.getText() + inputChar);
                    } else if(onKeyStrokeEvent.key == Util::Input::Key::Space) {
                        textField.text.setText(textField.text.getText() + " ");
                    } else if(onKeyStrokeEvent.key == Util::Input::Key::Backspace) {
                        textField.text.setText(textField.text.getText().substr(0, textField.text.getText().length() - 1));
                    }
                }
            );

            _glInitialized = false;
        }

        TextField::~TextField() {

        }

        void TextField::render() const {
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
        }

        void TextField::update(double deltaTime) {
            if(!isValid())
                validate();

            text.update(deltaTime);
        }

        void TextField::validate() const {
            TextField* thisConstless = const_cast<TextField*>(this);

            // (Re)build VBO
            GL::VertexBuffer::Data vertexData;
            std::vector<glm::vec4> vertices = getVertices();

            vertexData.data = vertices.data();
            vertexData.size = vertices.size() * sizeof(glm::vec4);
            vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, sizeof(glm::vec4) + sizeof(glm::vec4), nullptr));
            vertexData.pointers.push_back(GL::VertexAttrib(1, 4, GL_FLOAT, sizeof(glm::vec4) + sizeof(glm::vec4), (GLvoid*)sizeof(glm::vec4)));

            _vbo.bind();
                thisConstless->_vbo.setUsage(VertexBuffer::Usage::DynamicDraw);
                thisConstless->_vbo.setData(vertexData);
            _vbo.unbind();

            // Initialize VAO
            if(_glInitialized == false) {
                thisConstless->_vao.setDrawCount(vertices.size());
                thisConstless->_vao.setDrawTarget(VertexArray::DrawTarget::Triangles);

                _vao.bind();
                    thisConstless->_vao.attachVBO(&_vbo);
                    thisConstless->_vao.setAttribPointers();
                _vao.unbind();

                thisConstless->_glInitialized = true;
            }

            // Update button's text position
            thisConstless->text.updatePosition();

            thisConstless->setValid();
        }

        const glm::vec4& TextField::getColor() const {
            return _color;
        }

        float TextField::getAlpha() const {
            return _color.a;
        }

        void TextField::setColor(const glm::vec3& color) {
            setColor(glm::vec4(color, getAlpha()));
        }

        void TextField::setColor(const glm::vec4& color) {
            _color = color;

            setInvalid();
        }

        void TextField::setAlpha(const float alpha) {
            setColor(glm::vec4(getColor().r, getColor().g, getColor().b, alpha));
        }

        Program& TextField::getProgram() {
            static Program program(
                Shader("assets/shaders/utilGUIButton.vp", Shader::Type::VertexShader), 
                Shader("assets/shaders/utilGUIButton.fp", Shader::Type::FragmentShader)
            );

            return program;
        }

        std::vector<glm::vec4> TextField::getVertices() const {
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

            // Border
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borEnd.x, borStart.y - borWidth.y), border.getColor()); // top
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borStart.y), glm::vec2(borStart.x + borWidth.x, borEnd.y), border.getColor()); // left
            addRectangleVerticesWithColor(result, glm::vec2(borEnd.x   - borWidth.x, borStart.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // right
            addRectangleVerticesWithColor(result, glm::vec2(borStart.x, borEnd.y + borWidth.y), glm::vec2(borEnd.x, borEnd.y), border.getColor()); // bottom

            return result;
        }

    }

}
