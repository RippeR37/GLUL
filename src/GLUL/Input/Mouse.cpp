#include <GLUL/Window.h>
#include <GLUL/Input/Mouse.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace GLUL {

    namespace Input {

        void Mouse::setMode(CursorMode cursorMode) {
            setMode(cursorMode, GLUL::Windows::Active());
        }

        void Mouse::setMode(CursorMode cursorMode, GLUL::Window* window) {
            if(window) {
                int libMode = GLFW_CURSOR_NORMAL;

                switch(cursorMode) {
                    case CursorMode::Normal:   libMode = GLFW_CURSOR_NORMAL; break;
                    case CursorMode::Hidden:   libMode = GLFW_CURSOR_HIDDEN; break;
                    case CursorMode::Disabled: libMode = GLFW_CURSOR_DISABLED; break;

                    default: 
                        break;
                }

                glfwSetInputMode(window->getHandle(), GLFW_CURSOR, libMode);
            }
        }


        Input::Action Mouse::getState(MouseButton mouseButton) {
            return getState(mouseButton, GLUL::Windows::Active());
        }

        Input::Action Mouse::getState(MouseButton mouseButton, GLUL::Window* window) {
            Input::Action result = Input::Action::Release;

            if(window) {
                int libButton = GLFW_MOUSE_BUTTON_LEFT;

                switch(mouseButton) {
                    case MouseButton::Left:   libButton = GLFW_MOUSE_BUTTON_LEFT;   break;
                    case MouseButton::Right:  libButton = GLFW_MOUSE_BUTTON_RIGHT;  break;
                    case MouseButton::Middle: libButton = GLFW_MOUSE_BUTTON_MIDDLE; break;

                    default: 
                        break;
                }

                int libResult = glfwGetMouseButton(window->getHandle(), libButton);

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
            return getPosition(GLUL::Windows::Active());
        }

        glm::vec2 Mouse::getPosition(GLUL::Window* window) {
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
