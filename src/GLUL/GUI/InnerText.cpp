#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/InnerText.h>



namespace GLUL {

    namespace GUI {

        InnerText::InnerText(const Component& component) : _component(component) {
            setAlignment(Style::HorizontalAlignment::Center, Style::VerticalAlignment::Center);
        }

        InnerText& InnerText::operator=(const std::string& text) {
            setText(text);
            return *this;
        }

        void InnerText::update(double deltaTime) {
            _text.update(deltaTime);
        }

        void InnerText::render() const {
            _text.render();
        }

        void InnerText::setFont(const Font& font) {
            _text.setFont(font);

            updatePosition();
        }

        void InnerText::setFont(const Font* font) {
            _text.setFont(font);

            updatePosition();
        }

        void InnerText::setText(const std::string& text) {
            _text.setText(text);

            updatePosition();
        }

        void InnerText::setColor(const glm::vec3& color) {
            _text.setColor(color);

            updatePosition();
        }

        void InnerText::setColor(const glm::vec4& color) {
            _text.setColor(color);
        }

        void InnerText::setAlpha(float alpha) {
            _text.setAlpha(alpha);
        }

        void InnerText::setHorizontalAlignment(Style::HorizontalAlignment horizontalAlignment) {
            setAlignment(horizontalAlignment, getVerticalAlignment());
        }

        void InnerText::setVerticalAlignment(Style::VerticalAlignment verticalAlignment) {
            setAlignment(getHorizontalAlignment(), verticalAlignment);
        }

        void InnerText::setAlignment(Style::HorizontalAlignment horizontalAlignment, Style::VerticalAlignment verticalAlignment) {
            bool update = false;

            if(_horizontalAlignment != horizontalAlignment) {
                _horizontalAlignment = horizontalAlignment;
                update = true;
            }

            if(_verticalAlignment != verticalAlignment) {
                _verticalAlignment = verticalAlignment;
                update = true;
            }

            if(update)
                updatePosition();
        }

        const Font* InnerText::getFont() const {
            return _text.getFont();
        }

        const std::string& InnerText::getText() const {
            return _text.getText();
        }

        const glm::vec4& InnerText::getColor() const {
            return _text.getColor();
        }

        float InnerText::getAlpha() const {
            return _text.getAlpha();
        }
        
        Style::HorizontalAlignment InnerText::getHorizontalAlignment() const {
            return _horizontalAlignment;
        }

        Style::VerticalAlignment InnerText::getVerticalAlignment() const {
            return _verticalAlignment;
        }
        
        /**
         * TODO: fix this
         */
        void InnerText::updatePosition() {
            GLUL::Rectangle textBounds;
            float factorX, factorY;

            // Use font's height, not bounded
            textBounds = _text.getBounds();
            textBounds.setHeight(static_cast<float>(_text.getFontHeight()));

            switch(getHorizontalAlignment()) {
                case GUI::Style::HorizontalAlignment::Left:   factorX = 0.0f; break;
                case GUI::Style::HorizontalAlignment::Center: factorX = 0.5f; break;
                case GUI::Style::HorizontalAlignment::Right:  factorX = 1.0f; break;
                default: 
                    factorX = 0.5f;
            }

            switch(getVerticalAlignment()) {
                case GUI::Style::VerticalAlignment::Top:    factorY = 0.0f; break;
                case GUI::Style::VerticalAlignment::Center: factorY = 0.5f; break;
                case GUI::Style::VerticalAlignment::Bottom: factorY = 1.0f; break;
                default: 
                    factorY = 0.5f;
            }
           
            glm::vec2 padding = glm::vec2(
                 factorX * (_component.getSize().x - textBounds.getWidth()),
                 factorY * (_component.getSize().y - textBounds.getHeight())
            );

            _text.setPosition(_component.getScreenPosition().getPosition() + padding);
        }

    }

}
