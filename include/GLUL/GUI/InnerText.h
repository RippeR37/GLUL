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

                void setFont(const Font& font);
                void setFont(const Font* font);
                void setText(const std::string& text);
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setAlpha(float alpha);
                void setHorizontalAlignment(Style::HorizontalAlignment horizontalAlignment);
                void setVerticalAlignment(Style::VerticalAlignment verticalAlignment);
                void setAlignment(Style::HorizontalAlignment horizontalAlignment, Style::VerticalAlignment verticalAlignment);

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
