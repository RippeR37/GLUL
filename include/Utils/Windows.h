#ifndef UTILS_WINDOWS_H_INCLUDED
#define UTILS_WINDOWS_H_INCLUDED

#include <set>

struct GLFWwindow;

namespace Util {

    class Window;
    
    class Windows {
        friend class Window;

        public:
            static Window* Active();

            static Window* Get(Util::Window* window);
            static Window* Get(GLFWwindow* windowHandle);

        private:
            Windows();
            ~Windows();

            static void registerWindow(Util::Window* window);
            static void unregisterWindow(Util::Window* window);

            static void setActiveWindow(Util::Window* window);
            static void setActiveWindow(GLFWwindow* window);

            static Windows _instance;
            std::set<Util::Window*> _windows;
            Util::Window* _active;
    };
    
}

#endif