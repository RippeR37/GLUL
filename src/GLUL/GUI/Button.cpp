#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Button.h>


namespace GLUL {

    namespace GUI {

        Button::Button(const Base::Container& parent)
            : Base::Button(parent, new RectangularBackground(*this)) { }

        Button::Button(const Base::Container& parent, const glm::vec2& size, const glm::vec2& position)
            : Base::Button(parent, size, position, new RectangularBackground(*this)) { }

        void Button::_pushToBatch(G2D::TexturedBatch& texBatch) const {
            Base::Button::_pushToBatch(texBatch);

            // TODO:
            // - label
        }

    }

}
