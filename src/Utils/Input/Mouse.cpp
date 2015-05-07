#include <Utils/Window.h>
#include <Utils/Input/Mouse.h>

#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace Util {

    namespace Input {

        void Mouse::setMode(CursorMode cursorMode) {
            setMode(cursorMode, Util::Windows::Active());
        }

        void Mouse::setMode(CursorMode cursorMode, Util::Window* window) {
            int libMode;

            if(window) {
                switch(cursorMode) {
                    case CursorMode::Normal: libMode = GLFW_CURSOR_NORMAL; break;
                    case CursorMode::Hidden: libMode = GLFW_CURSOR_HIDDEN; break;
                    case CursorMode::Disabled: libMode = GLFW_CURSOR_DISABLED; break;

                    default: 
                        break;
                }

                glfwSetInputMode(window->getHandle(), GLFW_CURSOR, libMode);
            }
        }


        Input::Action Mouse::getState(MouseButton mouseButton) {
            return getState(mouseButton, Util::Windows::Active());
        }

        Input::Action Mouse::getState(MouseButton mouseButton, Util::Window* window) {
            Input::Action result = Input::Action::Release;
            int libButton;
            int libResult;

            if(window) {
                switch(mouseButton) {
                    case MouseButton::Left:   libButton = GLFW_MOUSE_BUTTON_LEFT;   break;
                    case MouseButton::Right:  libButton = GLFW_MOUSE_BUTTON_RIGHT;  break;
                    case MouseButton::Middle: libButton = GLFW_MOUSE_BUTTON_MIDDLE; break;

                    default: 
                        break;
                }

                libResult = glfwGetMouseButton(window->getHandle(), libButton);

                switch(libResult) {
                    case GLFW_PRESS:   result = Input::Action::Press;   break;
                    case GLFW_REPEAT:  result = Input::Action::Repeat;  break;
                    case GLFW_RELEASE: result = Input::Action::Release; break;

                    default: 
                        break;
                }
            }

            return result;
        }

        glm::vec2 Mouse::getPosition() {
            return getPosition(Util::Windows::Active());
        }

        glm::vec2 Mouse::getPosition(Util::Window* window) {
            glm::vec2 result = glm::vec2(0.0f, 0.0f);
            glm::dvec2 libResult;

            if(window) {
                glfwGetCursorPos(window->getHandle(), &libResult.x, &libResult.y);
                result = libResult;
            }

            return result;
        }

    }

}