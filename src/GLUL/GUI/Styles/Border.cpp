#include <GLUL/GUI/Styles/Border.h>


namespace GLUL {

    namespace GUI {

        namespace Style {

            Border::Border(Component& component) : _component(component) {
                _setWidth(0);
                _setOffset(0);
                _setColor(glm::vec4());
            }

            void Border::set(unsigned int width) {
                _setWidth(width);
                updateComponent();
            }

            void Border::set(unsigned int width, int offset) {
                _setWidth(width);
                _setOffset(offset);
                updateComponent();
            }

            void Border::set(unsigned int width, int offset, const glm::vec3& color) {
                _setWidth(width);
                _setOffset(offset);
                _setColor(color);
                updateComponent();
            }

            void Border::set(unsigned int width, int offset, const glm::vec4& color) {
                _setWidth(width);
                _setOffset(offset);
                _setColor(color);
                updateComponent();
            }

            void Border::setWidth(unsigned int width) {
                _setWidth(width);
                updateComponent();
            }

            void Border::setOffset(int offset) {
                _setOffset(offset);
                updateComponent();
            }

            void Border::setColor(const glm::vec3& color) {
                _setColor(color);
                updateComponent();
            }

            void Border::setColor(const glm::vec4& color) {
                _setColor(color);
                updateComponent();
            }

            unsigned int Border::getWidth() const {
                return _width;
            }

            int Border::getOffset() const {
                return _offset;
            }

            const glm::vec4& Border::getColor() const {
                return _color;
            }

            void Border::_setWidth(unsigned int width) {
                _width = width;
            }

            void Border::_setOffset(int offset) {
                _offset = offset;
            }

            void Border::_setColor(const glm::vec3& color) {
                _color = glm::vec4(color, 1.0f);
            }

            void Border::_setColor(const glm::vec4& color) {
                _color = color;
            }

            void Border::updateComponent() {
                _component.setInvalid();
                _component.validate();
            }

        }

    }

}
