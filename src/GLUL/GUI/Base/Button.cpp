#include <GLUL/GUI/Base/Button.h>
#include <GLUL/GUI/Base/Container.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Button::Button(const Container& parent, Background* background)
                : ComponentWithBackground(parent, background) { }

            Button::Button(const Container& parent, const glm::vec2& size, const glm::vec2& position, Background* background)
                : ComponentWithBackground(parent, size, position, background) { }

        }

    }

}
