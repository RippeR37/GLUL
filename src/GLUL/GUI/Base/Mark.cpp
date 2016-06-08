#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Base/Mark.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Mark::Mark(const Component& owner)
                : Mark(owner, 0.5f, glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f }) { }

            Mark::Mark(const Component& owner, float scale, const glm::vec3& color)
                : Mark(owner, glm::vec2 { scale }, glm::vec4 { color, 1.0f }) { }

            Mark::Mark(const Component& owner, float scale, const glm::vec4& color)
                : Mark(owner, glm::vec2 { scale }, color) { }

            Mark::Mark(const Component& owner, const glm::vec2& scale, const glm::vec3& color)
                : Mark(owner, scale, glm::vec4 { color, 1.0f }) { }

            Mark::Mark(const Component& owner, const glm::vec2& scale, const glm::vec4& color)
                : _owner(owner), _scale(scale), _color(color) { }

            const glm::vec4& Mark::getColor() const {
                return _color;
            }

            const glm::vec2& Mark::getScale() const {
                return _scale;
            }

            void Mark::set(float scale, const glm::vec3& color) {
                setScale(scale);
                setColor(color);
            }

            void Mark::set(float scale, const glm::vec4& color) {
                setScale(scale);
                setColor(color);
            }

            void Mark::set(const glm::vec2& scale, const glm::vec3& color) {
                setScale(scale);
                setColor(color);
            }

            void Mark::set(const glm::vec2& scale, const glm::vec4& color) {
                setScale(scale);
                setColor(color);
            }

            void Mark::setColor(const glm::vec3& color) {
                setColor(glm::vec4 { color, getColor().a });
            }

            void Mark::setColor(const glm::vec4& color) {
                _color = color;

                _invalidate();
            }

            void Mark::setScale(float scale) {
                setScale(glm::vec2 { scale });
            }

            void Mark::setScale(const glm::vec2& scale) {
                _scale = scale;

                _invalidate();
            }

            void Mark::_invalidate() {
                _owner.setInvalid();
            }

        }

    }

}
