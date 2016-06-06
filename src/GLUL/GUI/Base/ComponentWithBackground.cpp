#include <GLUL/GUI/Base/ComponentWithBackground.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            ComponentWithBackground::ComponentWithBackground(const Container& parent, Background* background)
                : Component(parent), _background(background) { }

            ComponentWithBackground::ComponentWithBackground(const Container& parent, const glm::vec2& size, const glm::vec2& position, Background* background)
                : Component(parent, size, position), _background(background) { }

            Background& ComponentWithBackground::getBackground() {
                return *_background;
            }

            void ComponentWithBackground::_pushToBatch(G2D::TexturedBatch& texBatch) const {
                _background->_pushToBatch(texBatch);
            }

        }

    }

}
