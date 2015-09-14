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

                void render() const;
                void update(double deltaTime);

                void validate() const;

                const Font* getFont() const;
                const std::string& getText() const;
                const glm::vec4& getColor() const;
                float getAlpha() const;
                float getScale() const;
                unsigned int getFontHeight() const;
                
                void setEnabled(bool flag);
                void setFocused(bool flag);
                void setVisible(bool flag);
                void setFont(const Font& font);
                void setFont(const Font* font);
                void setText(const std::string& text);
                void setSize(const glm::vec2& size);
                void setSize(unsigned int newHeight);
                void setScale(float scale);
                void setColor(const glm::vec3& color);
                void setColor(const glm::vec4& color);
                void setAlpha(float alpha);
                

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
