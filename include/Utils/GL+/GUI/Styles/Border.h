#ifndef UTILS_GL_GUI_STYLES_BORDER_H_INCLUDED
#define UTILS_GL_GUI_STYLES_BORDER_H_INCLUDED

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace GL {

    namespace GUI {

        namespace Style {

            class Border {
                public:
                    Border();
                    Border(unsigned int width, int offset, const glm::vec3& color);
                    Border(unsigned int width, int offset, const glm::vec4& color);

                    unsigned int width;
                    int offset;
                    glm::vec4 color;
                    
            };

        }

    }

}

#endif