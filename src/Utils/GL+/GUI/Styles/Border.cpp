#include <Utils/GL+/GUI/Styles/Border.h>

namespace GL {

    namespace GUI {

        namespace Style {

            Border::Border() : Border(0, 0, glm::vec4()) {

            }

            Border::Border(unsigned int width, int offset, const glm::vec3& color) {
                this->width = width;
                this->offset = offset;
                this->color = glm::vec4(color, 1.0f);
            }

            Border::Border(unsigned int width, int offset, const glm::vec4& color) {
                this->width = width;
                this->offset = offset;
                this->color = color;
            }

        }

    }

}