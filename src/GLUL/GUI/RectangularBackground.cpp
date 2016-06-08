#include <GLUL/G2D/TexturedRectangle.h>
#include <GLUL/GUI/Base/Component.h>
#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/RectangularBackground.h>


namespace GLUL {

    namespace GUI {

        RectangularBackground::RectangularBackground(const Base::Component& owner)
            : RectangularBackground(owner, glm::vec4 { 1.0f, 1.0f, 1.0f, 1.0f }) { }

        RectangularBackground::RectangularBackground(const Base::Component& owner, const glm::vec3& color)
            : RectangularBackground(owner, glm::vec4 { color, 1.0f }) { }

        RectangularBackground::RectangularBackground(const Base::Component& owner, const glm::vec4& color)
            : Base::Background(owner), _color(color) { }

        const glm::vec4& RectangularBackground::getColor() const {
            return _color;
        }

        void RectangularBackground::setColor(const glm::vec3& color) {
            setColor(glm::vec4 { color, getColor().a });
        }

        void RectangularBackground::setColor(const glm::vec4& color) {
            _color = color;

            _invalidate();
        }

        void RectangularBackground::_pushToBatch(G2D::TexturedBatch& texBatch) {
            if(_owner.isVisible()) {

                if(border.getWidth() > 0 && border.getColor().a > 0.0f)
                    _pushBorderToBatch(texBatch);

                if(_owner.getSize().x > 0.0f && _owner.getSize().y > 0.0f && getColor().a != 0)
                    _pushBackgroundToBatch(texBatch);

            }
        }

        void RectangularBackground::_pushBorderToBatch(G2D::TexturedBatch& texBatch) {
            glm::vec2 borderSize { static_cast<float>(border.getWidth()) };

            // Up (whole line)
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() + glm::vec2 { -borderSize.x, 0.0f },
                        { 1.0f, 1.0f },
                        border.getColor()
                    },
                    glm::vec2 { _owner.getSize().x + 2 * borderSize.x, borderSize.y },
                    glm::vec2 { 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );

            // Bottom (whole line)
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() - borderSize - glm::vec2 { 0.0f, _owner.getSize().y },
                        { 1.0f, 1.0f },
                        border.getColor()
                    },
                    glm::vec2 { _owner.getSize().x + 2 * borderSize.x, borderSize.y },
                    glm::vec2 { 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );

            // Left (without corners)
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() - glm::vec2 { borderSize.x, _owner.getSize().y },
                        { 1.0f, 1.0f },
                        border.getColor()
                    },
                    glm::vec2 { borderSize.x, _owner.getSize().y },
                    glm::vec2 { 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );

            // Right (without corners)
            texBatch.addPrimitive(
                G2D::TexturedRectangle {
                    G2D::TexturedPoint {
                        _owner.getScreenPosition() + glm::vec2 { _owner.getSize().x, -_owner.getSize().y },
                        { 1.0f, 1.0f },
                        border.getColor()
                    },
                    glm::vec2 { borderSize.x, _owner.getSize().y },
                    glm::vec2 { 0.0f }
                },
                _owner.getParent().getFont().getTexture()
            );
        }

        void RectangularBackground::_pushBackgroundToBatch(G2D::TexturedBatch& texBatch) {
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
