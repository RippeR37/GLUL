#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Types.h>

#include <glm/vec2.hpp>


namespace GLUL {

    class Window;

    namespace Input {

        class GLUL_API Mouse {
            public:
                void setMode(CursorMode cursorMode);
                void setMode(CursorMode cursorMode, GLUL::Window* window);

                static Input::Action getState(MouseButton mouseButton);
                static Input::Action getState(MouseButton mouseButton, GLUL::Window* window);

                static glm::vec2 getPosition();
                static glm::vec2 getPosition(GLUL::Window* window);
        };

    }

}
