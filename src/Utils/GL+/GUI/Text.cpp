#include <Utils/GL+/GUI/Text.h>
#include <Utils/Logger.h>

#include <cctype>

namespace GL {

    namespace GUI {

        Text::Text(Container* const parent) : Component(parent) {
            setFont(nullptr);
            setColor(glm::vec4(1.0f));
            setScale(1.0f);

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

        const float Text::getScale() const {
            return _scale;
        }

        const unsigned int Text::getFontHeight() const {
            unsigned int result = static_cast<unsigned int>((getFont() ? getFont()->getHeight() : 0) * getScale());

            return result;
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
            // [DEPRECATED] - size.x will not be used
            Util::Log::Stream("_Library").logWarning(
                "Use of deprecated functionality Text::setSize(const glm::vec2&) for text '" + 
                getText() + 
                "' - width will not be used"
            );

            setSize(static_cast<unsigned int>(size.y));
        }

        void Text::setSize(const unsigned int newHeight) {
            float oldFontHeight = static_cast<float>(getFont() ? getFont()->getHeight() : 1.0f);
            float newFontHeight = static_cast<float>(newHeight);

            setScale(newFontHeight / oldFontHeight);
        }

        void Text::setScale(const float scale) {
            _scale = scale;
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
            glm::vec2 baseLine = getScreenPosition().getPosition() - glm::vec2(0.0f, getScale() * getFont()->getAscender());
            glm::vec2 posCursor = baseLine;
            glm::vec2 bbTopRight = baseLine;
            glm::vec2 bbBottomLeft = baseLine;
            char character;
            bool isDrawn = true;

            for(int i = 0; i < _text.size(); ++i) {
                character = getText()[i];
                isDrawn = (std::isgraph(character) > 0);

                if(isDrawn) {
                    // Calcuations
                    texStart  = getFont()->getMetric(character).texPosStart;
                    texEnd    = getFont()->getMetric(character).texPosEnd;

                    posStart = posCursor + getScale() * glm::vec2(
                        getFont()->getMetric(character).glyphPos.x,
                        getFont()->getMetric(character).glyphPos.y - getFont()->getMetric(character).size.y
                        );
                    posEnd = posStart  + getScale() * getFont()->getMetric(character).size;

                    if(posStart.x < bbBottomLeft.x) bbBottomLeft.x = posStart.x;
                    if(posStart.y < bbBottomLeft.y) bbBottomLeft.y = posStart.y;
                    if(posEnd.x > bbTopRight.x) bbTopRight.x = posEnd.x;
                    if(posEnd.y > bbTopRight.y) bbTopRight.y = posEnd.y;

                    // Vertices
                    if(getFont()->getMetric(character).size.x > 0 && getFont()->getMetric(character).size.y > 0) {
                        result.emplace_back(posStart.x, posStart.y, texStart.x, texStart.y);
                        result.emplace_back(posEnd.x,   posStart.y, texEnd.x,   texStart.y);
                        result.emplace_back(posStart.x, posEnd.y,   texStart.x, texEnd.y);

                        result.emplace_back(posStart.x, posEnd.y,   texStart.x, texEnd.y);
                        result.emplace_back(posEnd.x,   posStart.y, texEnd.x,   texStart.y);
                        result.emplace_back(posEnd.x,   posEnd.y,   texEnd.x,   texEnd.y);
                    }
                }

                switch(character) {
                    case '\n': posCursor  = glm::vec2(baseLine.x, posCursor.y - getFont()->getLineHeight()); break;
                    case '\t': posCursor += getScale() * getFont()->getMetric(' ').advance * 4.0f; break;

                    default:
                        posCursor += getScale() * getFont()->getMetric(character).advance; break;
                }
            }

            const_cast<Text*>(this)->_size = bbTopRight - bbBottomLeft;

            return result;
        }

    }

}