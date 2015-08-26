#include <Utils/GL+/GUI/Events/MouseRelease.h>


namespace GL {

    namespace GUI {

        namespace Event {

            MouseRelease::MouseRelease(const Util::Input::MouseButton& button, const glm::vec2& position) : button(button), position(position) {
                
            }

        }

    }

}
