#ifndef UTILS_WINDOWS_H_INCLUDED
#define UTILS_WINDOWS_H_INCLUDED

#include <Utils/Config.h>

#include <string>
#include <unordered_set>
#include <unordered_map>


struct GLFWwindow;

namespace Util {

    class Window;
    
    class UTILS_API Windows {
        friend class Window;

        public:
            static Window* Active();

            static Window* Get(Util::Window* window);
            static Window* Get(GLFWwindow* handle);
            static Window* Get(const std::string& windowID);

            static void registerWindow(Util::Window* window, const std::string& windowID);
            static void registerWindow(Util::Window& window, const std::string& windowID);

        private:
            Windows();
            ~Windows();

            static void registerWindow(Util::Window* window);
            static void unregisterWindow(Util::Window* window);

            static void setActiveWindow(Util::Window* window);
            static void setActiveWindow(GLFWwindow* window);

            static Windows _instance;

            Util::Window* _active;
            std::unordered_map<GLFWwindow*, Util::Window*> _handles;
            std::unordered_map<std::string, Util::Window*> _namedWindows;
    };
    
}

#endif
