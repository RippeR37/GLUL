#include <Utils/Window.h>
#include <Utils/Input/Keyboard.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace Util {

    namespace Input {

        Input::Action Keyboard::getState(Key key) {
            return getState(key, Util::Windows::Active());
        }

        Input::Action Keyboard::getState(Key key, Util::Window* window) {
            Input::Action result = Input::Action::Release;

            if(window) {
                int libResult = glfwGetKey(window->getHandle(), static_cast<int>(key));

                switch(libResult) {
                    case GLFW_PRESS:    result = Input::Action::Press;   break;
                    case GLFW_REPEAT:   result = Input::Action::Repeat;  break;
                    case GLFW_RELEASE:  result = Input::Action::Release; break;

                    default: 
                        break;
                }
            }

            return result;
        }

    }

}
