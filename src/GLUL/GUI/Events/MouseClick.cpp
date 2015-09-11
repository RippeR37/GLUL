#include <GLUL/GUI/Events/MouseClick.h>


namespace GLUL {

    namespace GUI {

        namespace Event {

            MouseClick::MouseClick(const GLUL::Input::MouseButton& button, const glm::vec2& position) : button(button), position(position) { 
                
            }

        }

    }

}
