#pragma once

#include <GLUL/GUI/Text.h>
#include <GLUL/GUI/Styles/HorizontalAlignment.h>
#include <GLUL/GUI/Styles/VerticalAlignment.h>


namespace GLUL {

    namespace GUI {

        class GLUL_API InnerText {
            public:
                InnerText(const Component& component);

                InnerText& operator=(const std::string& text);

                void update(double deltaTime);
                void render() const;

                InnerText& setFont(const Font& font);
                InnerText& setFont(const Font* font);
                InnerText& setText(const std::string& text);
                InnerText& setColor(const glm::vec3& color);
                InnerText& setColor(const glm::vec4& color);
                InnerText& setAlpha(float alpha);
                InnerText& setHorizontalAlignment(Style::HorizontalAlignment horizontalAlignment);
                InnerText& setVerticalAlignment(Style::VerticalAlignment verticalAlignment);
                InnerText& setAlignment(Style::HorizontalAlignment horizontalAlignment, Style::VerticalAlignment verticalAlignment);

                const Font* getFont() const;
                const std::string& getText() const;
                const glm::vec4& getColor() const;
                float getAlpha() const;
                Style::HorizontalAlignment getHorizontalAlignment() const;
                Style::VerticalAlignment getVerticalAlignment() const;

            private:
                void updatePosition();

                Text _text;
                Style::HorizontalAlignment _horizontalAlignment;
                Style::VerticalAlignment _verticalAlignment;
                const Component& _component;

            private:
                friend class Button;
                friend class TextField;
        };

    }

}
