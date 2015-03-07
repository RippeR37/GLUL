#ifndef UTILS_GL_GUI_TEXT_H_INCLUDED
#define UTILS_GL_GUI_TEXT_H_INCLUDED

#include <Utils/GL+/GUI/Component.h>
#include <Utils/GL+/GUI/Font.h>

#include <Utils/GL+/Program.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>

namespace GL {

    namespace GUI {

        class Text : public Component {
            public:
                Text(Container* const parent = nullptr);
                ~Text();

                void render();
                void update(double deltaTime);

                void validate();

                void setFont(const Font* font);
                void setText(const std::string& text);
                void setPosition(const glm::vec2& position);

                const Font* getFont() const;
                const std::string& getText() const;
                const glm::vec2& getPosition() const;

            private:
                std::vector<glm::vec4> getVertices() const;

                const Font* _font;
                std::string _text;
                glm::vec2 _position;

                bool _glInitialized;
                VertexArray _vao;
                VertexBuffer _vbo;

            private:
                static Program& getProgram();
        };

    }

}

#endif