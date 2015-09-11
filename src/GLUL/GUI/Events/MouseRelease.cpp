#include <GLUL/GUI/Events/MouseRelease.h>


namespace GLUL {

    namespace GUI {

        namespace Event {

            MouseRelease::MouseRelease(const GLUL::Input::MouseButton& button, const glm::vec2& position) : button(button), position(position) {
                
            }

        }

    }

}
