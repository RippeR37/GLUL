#include <GLUL/Window.h>
#include <GLUL/Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>


namespace GLUL {

    // Static instance of Windows class
    Windows Windows::_instance;
    
    Windows::Windows() {
        setActiveWindow(static_cast<GLUL::Window*>(nullptr));
    }

    Windows::~Windows() {
        setActiveWindow(static_cast<GLUL::Window*>(nullptr));
    }

    GLUL::Window* Windows::Active() {
        return _instance._active;
    }

    GLUL::Window* Windows::Get(GLUL::Window* window) {
        GLUL::Window* result = nullptr;

        if(window)
            result = Get(window->getHandle());

        return result;
    }

    GLUL::Window* Windows::Get(GLFWwindow* handle) {
        GLUL::Window* result = nullptr;

        auto iterator = _instance._handles.find(handle);
        if(iterator != _instance._handles.end())
            result = iterator->second;

        return result;
    }

    Window* Windows::Get(const std::string& windowID) {
        GLUL::Window* result = nullptr;

        auto iterator = _instance._namedWindows.find(windowID);
        if(iterator != _instance._namedWindows.end())
            result = iterator->second;

        return result;
    }

    void Windows::registerWindow(GLUL::Window* window, const std::string& windowID) {
        if(window) {
            _instance._namedWindows[windowID] = window;
        }
    }
    
    void Windows::registerWindow(GLUL::Window& window, const std::string& windowID) {
        registerWindow(&window, windowID);
    }
            

    void Windows::registerWindow(GLUL::Window* window) {
        if(window) {
            _instance._handles[window->getHandle()] = window;
        }
    }

    void Windows::unregisterWindow(GLUL::Window* window) {
        _instance._handles.erase(window->getHandle());

        for(auto iter = _instance._namedWindows.begin(); iter != _instance._namedWindows.end(); ) {
            if(iter->second == window)
                iter = _instance._namedWindows.erase(iter);
            else 
                ++iter;
        }
    }

    void Windows::setActiveWindow(GLUL::Window* window) {
        _instance._active = window;
    }
    
    void Windows::setActiveWindow(GLFWwindow* window) {
        GLUL::Window* activeWindow = nullptr;
        
        if(window)
            activeWindow = Windows::Get(window);

        setActiveWindow(activeWindow);
    }
    
}
