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

        if(window)
            result = Get(window->getHandle());

        return result;
    }

    Util::Window* Windows::Get(GLFWwindow* handle) {
        Util::Window* result = nullptr;

        auto iterator = _instance._handles.find(handle);
        if(iterator != _instance._handles.end())
            result = iterator->second;

        return result;
    }

    Window* Windows::Get(const std::string& windowID) {
        Util::Window* result = nullptr;

        auto iterator = _instance._namedWindows.find(windowID);
        if(iterator != _instance._namedWindows.end())
            result = iterator->second;

        return result;
    }

    void Windows::registerWindow(Util::Window* window, const std::string& windowID) {
        if(window) {
            _instance._namedWindows[windowID] = window;
        }
    }
    
    void Windows::registerWindow(Util::Window& window, const std::string& windowID) {
        registerWindow(&window, windowID);
    }
            

    void Windows::registerWindow(Util::Window* window) {
        if(window) {
            _instance._handles[window->getHandle()] = window;
        }
    }

    void Windows::unregisterWindow(Util::Window* window) {
        _instance._handles.erase(window->getHandle());

        for(auto iter = _instance._namedWindows.begin(); iter != _instance._namedWindows.end(); ) {
            if(iter->second == window)
                iter = _instance._namedWindows.erase(iter);
            else 
                ++iter;
        }
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