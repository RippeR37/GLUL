#ifndef UTILS_INPUT_KEYBOARD_H_INCLUDED
#define UTILS_INPUT_KEYBOARD_H_INCLUDED

#include <Utils/Input/Types.h>

#include <glm/vec2.hpp>

namespace Util {

    class Window;

    namespace Input {

        class Keyboard {
            public:
                static Input::Action getState(Key key);
                static Input::Action getState(Key key, Util::Window* window);
        };

    }

}

#endif