#include <GLUL/GUI/Base/Border.h>
#include <GLUL/GUI/Base/Component.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Border::Border(const Component& owner)
                : Border(owner, 0, glm::vec4 {}) { }

            Border::Border(const Component& owner, unsigned int width, const glm::vec3& color)
                : Border(owner, width, glm::vec4 { color, 1.0f }) { }

            Border::Border(const Component& owner, unsigned int width, const glm::vec4& color)
                : _owner(owner), _width(width), _color(color) { }

            unsigned int Border::getWidth() const {
                return _width;
            }

            const glm::vec4& Border::getColor() const {
                return _color;
            }

            void Border::setWidth(unsigned int width) {
                _width = width;

                _invalidate();
            }

            void Border::setColor(const glm::vec3& color) {
                setColor(glm::vec4 { color, getColor().a });
            }

            void Border::setColor(const glm::vec4& color) {
                _color = color;

                _invalidate();
            }

            void Border::_invalidate() {
                _owner.setInvalid();
            }

        }

    }

}
