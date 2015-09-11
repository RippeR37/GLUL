#include <GLUL/Frameworks/Application.h>
#include <GLUL/Logger.h>


namespace FW {

    Application::Application() : Window(_window) {
        GLUL::Log::LibraryStream();
        GLUL::Windows::registerWindow(Window, "FW::Application::Window::1");

        setArguments(0, nullptr);
        _state = nullptr;
    }

    Application::~Application() {

    }

    void Application::run(GLUL::Interface::State* initialState) {
        setState(initialState);

        while(getState() != GLUL::Interface::State::Quit) {
            getWindow().update();

            getState()->_update(getWindow().getFrameTime());
            getState()->_render();

            setState(getState()->getNext());
        }
    }

    void Application::signalExit() {
        if(getState())
            getState()->signalExit();
    }

    const std::string& Application::getArgument(int id) throw(std::out_of_range) {
        return _arguments.at(id);
    }

    const std::vector<std::string>& Application::getArguments() {
        return _arguments;
    }

    void Application::setArguments(int argumentCount, char* arguments[]) {
        _arguments.resize(argumentCount);

        for(int i = 0; i < argumentCount; ++i)
            _arguments[i] = std::string(arguments[i]);
    }


    GLUL::Window& Application::getWindow() {
        return _window;
    }

    GLUL::Interface::State* Application::getState() {
        return _state;
    }

    void Application::setState(GLUL::Interface::State* const newState) {
        if(getState() != newState) {
            if(getState() != nullptr)
                getState()->_onUnload();

            _state = newState;

            if(getState() != nullptr)
                getState()->_onLoad();
        }
    }

}
