#include <GLUL/G2D/Text.h>
#include <GLUL/G2D/TexturedQuad.h>

#include <cctype>


namespace GLUL {

    namespace G2D {

        Text::Text() : _alignment(Alignment::Left), _color({ 1.0f }) { }

        Text::Text(const std::string& text)
            : Text()
        {
            setText(text);
        }

        Text::Text(const std::string& text, const glm::vec2& position)
            : Text(text)
        {
            setPosition(position);
        }

        Text::Text(const std::string& text, const glm::vec2& position, Alignment alignment)
            : Text(text, position)
        {
            setAlignment(alignment);
        }

        Text::Text(const std::string& text, const glm::vec2& position, const glm::vec3& color)
            : Text(text, position, glm::vec4 { color, 1.0f }) { }

        Text::Text(const std::string& text, const glm::vec2& position, const glm::vec3& color, Alignment alignment)
            : Text(text, position, glm::vec4 { color, 1.0f }, alignment) { }

        Text::Text(const std::string& text, const glm::vec2& position, const glm::vec4& color)
            : Text(text, position)
        {
            setColor(color);
        }

        Text::Text(const std::string& text, const glm::vec2& position, const glm::vec4& color, Alignment alignment)
            : Text(text, position, color)
        {
            setAlignment(alignment);
        }

        Text& Text::operator=(const std::string& text) {
            setText(text);

            return *this;
        }

        Text::operator const std::string&() const {
            return getText();
        }

        void Text::render(const Font& font) const {
            render(TexturedGeometryBatch::getDefaultProgram(), font);
        }

        void Text::render(const GL::Program& program, const Font& font) const {
            static TexturedGeometryBatch texGeometryBatch;

            texGeometryBatch.addText(*this, font);
            texGeometryBatch.compute();
            texGeometryBatch.render(program);
            texGeometryBatch.clear();
        }

        void Text::setText(const std::string& text) {
            _text = text;
        }

        const std::string& Text::getText() const {
            return _text;
        }

        void Text::setPosition(const glm::vec2& position) {
            _position = position;
        }

        const glm::vec2& Text::getPosition() const {
            return _position;
        }

        void Text::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void Text::setColor(const glm::vec4& color) {
            _color = color;
        }

        const glm::vec4& Text::getColor() const {
            return _color;
        }

        void Text::setAlignment(Alignment alignment) {
            _alignment = alignment;
        }

        Text::Alignment Text::getAlignment() const {
            return _alignment;
        }

        void Text::_moveCursor(glm::vec2& cursorPosition, char character, const Font& font) const {
            const glm::vec2& basePoint = getPosition();

            switch(character) {
                case '\n':
                    cursorPosition = { basePoint.x, (cursorPosition.y - font.getLineHeight()) };
                    break;

                case '\t':
                    cursorPosition += font.getMetricOf(' ').advance * 4.0f;
                    break;

                default:
                    cursorPosition += font.getMetricOf(character).advance;
                    break;
            }
        }

        void Text::_pushToBatch(TexturedGeometryBatch& texGeometryBatch, const Font& font) const {
            glm::vec2 cursorPos = getPosition();

            for(char character : getText())
            {
                bool isDrawn = (std::isgraph(character) > 0);
                auto& metric = font.getMetricOf(character);
                auto characterPos = cursorPos + metric.glyphPos - glm::vec2 { 0.0f, metric.size.y };

                if(isDrawn)
                    texGeometryBatch.addPrimitive(
                        TexturedQuad {
                            { characterPos, metric.texPosStart, getColor() },
                            metric.size,
                            metric.texPosEnd - metric.texPosStart
                        },
                        font.getTexture()
                    );

                _moveCursor(cursorPos, character, font);
            }
        }

    }

}
