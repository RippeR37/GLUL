#include <GLUL/GUI/Base/Panel.h>
#include <GLUL/GUI/Events/ValueChange.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Panel::Panel(const Container& parent)
                : Panel(parent, {}, {}) { }

            Panel::Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size)
                : Panel(parent, position, size, size) { }

            Panel::Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& areaSize)
                : Container(parent, position, size), _areaSize(areaSize) { }

            void Panel::validate() const {
                // TODO: scrollbars logic validation

                Container::validate();
            }

            const glm::vec2 Panel::getScreenPosition() const {
                auto screenPos = Container::getScreenPosition();
                auto offset = getOffset();

                return screenPos - offset;
            }

            const glm::vec2 Panel::getOffset() const {
                return {
                    // TODO:
                    // _scrollbarHorizontal.getValue(),
                    // _scrollbarVertical.getMax() - _scrollbarVertical.getValue()
                };
            }

            const glm::vec2& Panel::getAreaSize() const {
                return _areaSize;
            }

            void Panel::setAreaSize(const glm::vec2& areaSize) {
                _areaSize = areaSize;

                setInvalid();
            }

        }

    }

}
