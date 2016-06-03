#include <GLUL/GUI/Button.h>
#include <GLUL/GUI/Container.h>


namespace GLUL {

    namespace GUI {

        Button::Button(const Container& parent)
            : Button(parent, {}, {}) { }

        Button::Button(const Container& parent, const glm::vec2& size, const glm::vec2& position)
            : Button(parent, size, position, "Button") { }

        Button::Button(const Container& parent, const glm::vec2& size, const glm::vec2& position, const std::string& text)
            : Component(parent, size, position)
        {
            setText(text);
        }

        const std::string& Button::getText() const {
            return _text;
        }

        void Button::setText(const std::string& text) {
            _text = text;

            setInvalid();
        }

        void Button::_pushToBatch(G2D::TexturedBatch& texBatch) const {
            (void) texBatch;
            // TODO: implement this using G2D module
        }

    }

}
