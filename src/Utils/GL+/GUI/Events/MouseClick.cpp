#include <Utils/GL+/GUI/Events/MouseClick.h>

namespace GL {

    namespace GUI {

        namespace Event {

            MouseClick::MouseClick(const Util::Input::MouseButton& button, const glm::vec2& position) : button(button), position(position) { 
                
            }

        }

    }

}