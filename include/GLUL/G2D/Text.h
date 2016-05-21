#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/Font.h>
#include <GLUL/G2D/TexturedShape.h>

#include <functional>
#include <string>


namespace GLUL {

    namespace G2D {

        class GLUL_API Text : public TexturedShape {
            public:
                Text();
                Text(const Font& font, unsigned int height = 12u);
                Text(const Font& font, std::string& text, unsigned int height = 12u);

                void bindFont(const Font& font);

                void setHeight(unsigned int height);
                void setText(const std::string& text);
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);

                unsigned int getHeight() const;
                const std::string& getText() const;
                const glm::vec4& getColor() const;

            protected:
                glm::vec4 _color;
                std::string _text;
                std::reference_wrapper<Font> _font;
        };

    }

}
