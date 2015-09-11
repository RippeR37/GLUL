#pragma once

#include <GLUL/Config.h>
#include <GLUL/Input/Types.h>

#include <glm/vec2.hpp>


namespace GLUL {

    class Window;

    namespace Input {

        class GLUL_API Keyboard {
            public:
                static Input::Action getState(Key key);
                static Input::Action getState(Key key, GLUL::Window* window);
        };

    }

}
