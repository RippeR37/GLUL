#pragma once

#include <GLUL/Config.h>

#include <string>
#include <unordered_set>
#include <unordered_map>


struct GLFWwindow;

namespace GLUL {

    class Window;
    
    class GLUL_API Windows {
        friend class Window;

        public:
            static Window* Active();

            static Window* Get(GLUL::Window* window);
            static Window* Get(GLFWwindow* handle);
            static Window* Get(const std::string& windowID);

            static void registerWindow(GLUL::Window* window, const std::string& windowID);
            static void registerWindow(GLUL::Window& window, const std::string& windowID);

        private:
            Windows();
            ~Windows();

            static void registerWindow(GLUL::Window* window);
            static void unregisterWindow(GLUL::Window* window);

            static void setActiveWindow(GLUL::Window* window);
            static void setActiveWindow(GLFWwindow* window);

            static Windows _instance;

            GLUL::Window* _active;
            std::unordered_map<GLFWwindow*, GLUL::Window*> _handles;
            std::unordered_map<std::string, GLUL::Window*> _namedWindows;
    };
    
}
