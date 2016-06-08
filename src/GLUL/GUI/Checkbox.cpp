#include <GLUL/G2D/TexturedRectangle.h>
#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Checkbox.h>


namespace GLUL {

    namespace GUI {

        Checkbox::Checkbox(const Base::Container& parent, bool isSet)
            : Base::Checkbox(parent, isSet, new RectangularBackground(*this)) { }

        Checkbox::Checkbox(const Base::Container& parent, float size, const glm::vec2& position, bool isSet)
            : Checkbox(parent, glm::vec2 { size }, position, isSet) { }

        Checkbox::Checkbox(const Base::Container& parent, const glm::vec2& size, const glm::vec2& position, bool isSet)
            : Base::Checkbox(parent, size, position, isSet, new RectangularBackground(*this)) { }

        void Checkbox::_pushToBatch(G2D::TexturedBatch& texBatch) const {
            Base::Checkbox::_pushToBatch(texBatch);

            if(isSet())
                _pushMarkToBatch(texBatch);
        }

        void Checkbox::_pushMarkToBatch(G2D::TexturedBatch& texBatch) const {
            glm::vec2 realScreenPosition = _getRealScreenPosition();

            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        realScreenPosition + 0.5f * (glm::vec2 { getSize().x, -getSize().y } -(getSize() * mark.getScale())),
                        glm::vec2 { 1.0f },
                        mark.getColor()
                    },
                    getSize() * mark.getScale(),
                    glm::vec2 { 0.0f }
                },
                getParent().getFont().getTexture()
            );
        }

    }

}
