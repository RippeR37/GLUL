#pragma once

#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Component.h>
#include <GLUL/GUI/Font.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>


namespace GLUL {

    namespace GUI {

        class GLUL_API Text : public Component {
            public:
                Text(Container& parent);
                Text(Container* const parent = nullptr);
                ~Text();

                const Text& render() const;
                Text& update(double deltaTime);

                const Text& validate() const;

                const Font* getFont() const;
                const std::string& getText() const;
                const glm::vec4& getColor() const;
                float getAlpha() const;
                float getScale() const;
                unsigned int getFontHeight() const;
                
                Text& setEnabled(bool flag);
                Text& setFocused(bool flag);
                Text& setVisible(bool flag);
                Text& setFont(const Font& font);
                Text& setFont(const Font* font);
                Text& setText(const std::string& text);
                Text& setSize(const glm::vec2& size);
                Text& setSize(unsigned int newHeight);
                Text& setScale(float scale);
                Text& setColor(const glm::vec3& color);
                Text& setColor(const glm::vec4& color);
                Text& setAlpha(float alpha);
                Text& setPosition(const glm::vec2& position);
                Text& setPosition(const GLUL::Point& position);
                

            private:
                std::vector<glm::vec4> getVertices() const;

                const Font* _font;
                std::string _text;
                glm::vec4 _color;
                float _scale;

                bool _glInitialized;
                GL::VertexArray _vao;
                GL::VertexBuffer _vbo;

            private:
                static GL::Program& getProgram();
        };

    }

}
