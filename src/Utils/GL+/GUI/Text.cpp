#include <Utils/GL+/GUI/Text.h>
#include <Utils/Logger.h>

namespace GL {

    namespace GUI {

        Text::Text(Container* const parent) : Component(parent) {
            setFont(nullptr);
            setColor(glm::vec4(1.0f));

            _glInitialized = false;
        }

        Text::~Text() {

        }

        void Text::render() const {
            if(isVisible() && getAlpha() > 0.0f) {
                if(_font == nullptr) {
                    Util::Log::Stream("_Library").logError("[GUI] Attempt to render render text '" + _text + "' without font");
                    return;
                }

                if(!isValid())
                    validate();

                // Render using font
                if(_text != "") {
                    _font->getTexture().bind();

                    getProgram().use();
                    getProgram()["glyphAtlas"].setSampler(0);
                    getProgram()["fontColor"].setVec(getColor());

                    _vao.bind();
                    _vao.drawArrays();
                    _vao.unbind();

                    getProgram().unbind();

                    _font->getTexture().unbind();
                }
            }
        }

        void Text::update(double deltaTime) {
            if(!isValid())
                validate();

            // Nothing to update here
        }

        void Text::validate() const {
            Text* thisConstless = const_cast<Text*>(this);

            if(_text != "" && _font != nullptr) {
                // (Re)build VBO
                GL::VertexBuffer::Data vertexData;
                std::vector<glm::vec4> vertices = getVertices();

                vertexData.data = vertices.data();
                vertexData.size = vertices.size() * sizeof(glm::vec4);
                vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));


                _vbo.bind();
                    thisConstless->_vbo.setUsage(VertexBuffer::Usage::DynamicDraw);
                    thisConstless->_vbo.setData(vertexData);
                _vbo.unbind();


                // Initialize VAO
                if(_glInitialized == false) {
                    thisConstless->_vao.setDrawCount(vertices.size());                                               /// NEEDS TO CHANGE !!!
                    thisConstless->_vao.setDrawTarget(VertexArray::DrawTarget::Triangles);

                    _vao.bind();
                        thisConstless->_vao.attachVBO(&_vbo);
                        thisConstless->_vao.setAttribPointers();
                    _vao.unbind();

                    thisConstless->_glInitialized = true;
                }
            }

            thisConstless->setValid();
        }

        const Font* Text::getFont() const {
            return _font;
        }

        const std::string& Text::getText() const {
            return _text;
        }

        const glm::vec4& Text::getColor() const {
            return _color;
        }

        const float Text::getAlpha() const {
            return _color.a;
        }
        
        void Text::setEnabled(bool flag) {
            _isEnabled = flag;
        }

        void Text::setFocused(bool flag) {
            _isFocused = flag;
        }

        void Text::setVisible(bool flag) {
            if(_isVisible != flag) {
                _isVisible = flag;

                setInvalid();
            }
        }

        void Text::setFont(const Font* font) {
            _font = font;

            setInvalid();
        }

        void Text::setText(const std::string& text) {
            _text = text;

            setInvalid();
        }

        void Text::setSize(const glm::vec2& size) {
            //TODO: Allow setSize() to change size (scale?) of rendered text

            (void) size;
        }

        void Text::setColor(const glm::vec3& color) {
            setColor(glm::vec4(color, getAlpha()));
        }

        void Text::setColor(const glm::vec4& color) {
            _color = color;
        }

        void Text::setAlpha(const float alpha) {
            setColor(glm::vec4(getColor().r, getColor().g, getColor().b, alpha));
        }

        Program& Text::getProgram() {
            static Program program(
                Shader("assets/shaders/utilGUIText.vp", Shader::Type::VertexShader), 
                Shader("assets/shaders/utilGUIText.fp", Shader::Type::FragmentShader)
            );

            return program;
        }

        std::vector<glm::vec4> Text::getVertices() const {
            std::vector<glm::vec4> result;

            glm::vec2 posStart, posEnd;
            glm::vec2 texStart, texEnd;
            glm::vec2 posCursor = getScreenPosition().getPosition();
            char character;

            for(int i = 0; i < _text.size(); ++i) {
                character = _text[i];
                texStart  = _font->getMetric(character).texPosStart;
                texEnd    = _font->getMetric(character).texPosEnd;

                // Calcuations
                posStart = posCursor + glm::vec2(
                    _font->getMetric(character).glyphPos.x, 
                    _font->getMetric(character).glyphPos.y - _font->getMetric(character).size.y
                );
                posEnd   = posStart  + _font->getMetric(character).size;
                posCursor += _font->getMetric(character).advance;

                // Vertices
                if(_font->getMetric(character).size.x > 0 && _font->getMetric(character).size.y > 0) {
                    result.emplace_back(posStart.x, posStart.y, texStart.x, texStart.y);
                    result.emplace_back(posEnd.x,   posStart.y, texEnd.x,   texStart.y);
                    result.emplace_back(posStart.x, posEnd.y,   texStart.x, texEnd.y);

                    result.emplace_back(posStart.x, posEnd.y,   texStart.x, texEnd.y);
                    result.emplace_back(posEnd.x,   posStart.y, texEnd.x,   texStart.y);
                    result.emplace_back(posEnd.x,   posEnd.y,   texEnd.x,   texEnd.y);
                }
            }

            const_cast<Text*>(this)->_size = posEnd - getPosition().getPosition();

            return result;
        }

    }

}