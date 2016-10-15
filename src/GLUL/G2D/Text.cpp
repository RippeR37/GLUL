#include <GLUL/String.h>
#include <GLUL/G2D/Text.h>
#include <GLUL/G2D/TexturedRectangle.h>

#include <cctype>


namespace GLUL {

    namespace G2D {

        Text::Text() : _color(glm::vec4 { 1.0f }), _alignment(Alignment::Left) { }

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
            render(TexturedBatch::getDefaultProgram(), font);
        }

        void Text::render(const GL::Program& program, const Font& font) const {
            static TexturedBatch texBatch;

            texBatch.addText(*this, font);
            texBatch.compute();
            texBatch.render(program);
            texBatch.clear();
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

        void Text::moveCursor(glm::vec2& cursorPosition, const glm::vec2& baseline, char character, const Font& font) {
            switch(character) {
                case '\n':
                    cursorPosition = { baseline.x, (cursorPosition.y - font.getLineHeight()) };
                    break;

                case '\t':
                    cursorPosition += font.getMetricOf(' ').advance * 4.0f;
                    break;

                default:
                    cursorPosition += font.getMetricOf(character).advance;
                    break;
            }
        }

        void Text::_alignCursor(glm::vec2& cursorPos, char character, unsigned int& line, const std::vector<float>& lineAlignments) const {
            if(character == '\n' && line < lineAlignments.size())
                cursorPos.x = std::round(cursorPos.x - lineAlignments[line++]);
        }

        void Text::_pushToBatch(TexturedBatch& texBatch, const Font& font) const {
            auto lineAlignments = _getLinesAlignment(font, getText(), getAlignment());
            auto cursorPos = getPosition();
            auto line = 0u;

            _alignCursor(cursorPos, '\n', line, lineAlignments);

            for(char character : getText())
            {
                bool isDrawn = (std::isgraph(character) > 0);
                auto& metric = font.getMetricOf(character);
                auto characterPos = cursorPos + metric.glyphPos - glm::vec2 { 0.0f, metric.size.y };

                if(isDrawn)
                    texBatch.addPrimitive(
                        TexturedRectangle {
                            { characterPos, metric.texPosStart, getColor() },
                            metric.size,
                            metric.texPosEnd - metric.texPosStart
                        },
                        font.getTexture()
                    );

                moveCursor(cursorPos, getPosition(), character, font);
                _alignCursor(cursorPos, character, line, lineAlignments);
            }
        }

        float Text::_getLineAlignment(const Font& font, const std::string& text, Alignment alignment) const {
            auto bounds = font.getBoundsOf(text);
            float alignFactor;

            switch(alignment) {
                case Alignment::Left:   alignFactor = 0.0f; break;
                case Alignment::Center: alignFactor = 0.5f; break;
                case Alignment::Right:  alignFactor = 1.0f; break;

                default:
                    alignFactor = 0.0f;
            }

            return alignFactor * bounds.x;
        }

        std::vector<float> Text::_getLinesAlignment(const Font& font, const std::string& text, Alignment alignment) const {
            std::vector<float> result;
            auto lines = String::split(text, '\n', false);

            result.reserve(lines.size());

            for(const auto& line : lines)
                result.push_back(_getLineAlignment(font, line, alignment));

            // Always return at least one element (for first line)
            if(result.empty())
                result.push_back(0.0f);

            return result;
        }

    }

}
