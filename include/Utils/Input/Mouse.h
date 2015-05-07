#ifndef UTILS_INPUT_MOUSE_H_INCLUDED
#define UTILS_INPUT_MOUSE_H_INCLUDED

#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>

namespace Util {

    class Window;

    namespace Input {

        class Mouse {
            public:
                void setMode(CursorMode cursorMode);
                void setMode(CursorMode cursorMode, Util::Window* window);

                static Input::Action getState(MouseButton mouseButton);
                static Input::Action getState(MouseButton mouseButton, Util::Window* window);

                static glm::vec2 getPosition();
                static glm::vec2 getPosition(Util::Window* window);
        };

    }

}

#endif