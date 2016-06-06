#include <GLUL/G2D/TexturedRectangle.h>
#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/RectangleBackground.h>


namespace GLUL {

    namespace GUI {

        RectangleBackground::RectangleBackground(const Base::Component& owner)
            : RectangleBackground(owner, glm::vec4 { 1.0f }) { }

        RectangleBackground::RectangleBackground(const Base::Component& owner, const glm::vec3& color)
            : RectangleBackground(owner, glm::vec4 { color, 1.0f }) { }

        RectangleBackground::RectangleBackground(const Base::Component& owner, const glm::vec4& color)
            : Base::Background(owner), _color(color) { }

        const glm::vec4& RectangleBackground::getColor() const {
            return _color;
        }

        void RectangleBackground::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void RectangleBackground::setColor(const glm::vec4& color) {
            _color = color;

            _invalidate();
        }

        void RectangleBackground::_pushToBatch(G2D::TexturedBatch& texBatch) {
            glm::vec2 borderSize { static_cast<float>(border.getWidth()) };

            // Border
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() - glm::vec2 { 0.0f, _owner.getSize().y } - borderSize,
                        { 1.0f, 1.0f },
                        border.getColor()
                    },
                    _owner.getSize() + (2.0f * borderSize),
                    { 0.0f, 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );

            // Background
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() - glm::vec2 { 0.0f, _owner.getSize().y },
                        { 1.0f, 1.0f },
                        getColor()
                    },
                    _owner.getSize(),
                    { 0.0f, 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );

        }

    }

}
