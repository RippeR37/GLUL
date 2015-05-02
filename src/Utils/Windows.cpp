#include <Utils/Window.h>
#include <Utils/Windows.h>

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <algorithm>

namespace Util {

    // Static instance of Windows class
    Windows Windows::_instance;
    
    Windows::Windows() {
        setActiveWindow(static_cast<Util::Window*>(nullptr));
    }

    Windows::~Windows() {
        setActiveWindow(static_cast<Util::Window*>(nullptr));
    }

    Util::Window* Windows::Active() {
        return _instance._active;
    }

    Util::Window* Windows::Get(Util::Window* window) {
        Util::Window* result = nullptr;

        auto iterator = _instance._windows.find(window);

        if(iterator != _instance._windows.end())
            result = *iterator;

        return result;
    }

    Util::Window* Windows::Get(GLFWwindow* windowHandle) {
        Util::Window* result = nullptr;

        auto iterator = std::find_if(
            _instance._windows.begin(), _instance._windows.end(), 
            [windowHandle](Util::Window* window) { return window->getHandle() == windowHandle; }
        );

        if(iterator != _instance._windows.end())
            result = *iterator;

        return result;
    }
            

    void Windows::registerWindow(Util::Window* window) {
        if(window)
            _instance._windows.insert(window);
    }

    void Windows::unregisterWindow(Util::Window* window) {
        _instance._windows.erase(window);
    }

    void Windows::setActiveWindow(Util::Window* window) {
        _instance._active = window;
    }
    
    void Windows::setActiveWindow(GLFWwindow* window) {
        Util::Window* activeWindow = nullptr;
        
        if(window)
            activeWindow = Windows::Get(window);

        setActiveWindow(activeWindow);
    }
    

}