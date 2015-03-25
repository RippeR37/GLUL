#include <Utils/Frameworks/Application.h>
#include <Utils/Logger.h>

namespace FW {

    Application::Application() : Window(_window) {
        Util::Log::LibraryStream();
        setArguments(0, nullptr);
    }

    Application::~Application() {

    }

    void Application::run(Util::Interface::State* initialState) {
        setState(initialState);

        while(getState() != Util::Interface::State::Quit) {
            getWindow().update();

            getState()->handleInput();
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


    Util::Window& Application::getWindow() {
        return _window;
    }

    Util::Interface::State* Application::getState() {
        return _state;
    }

    void Application::setState(Util::Interface::State* const newState) {
        if(getState() != newState) {
            if(getState() != nullptr)
                getState()->_onUnload();

            _state = newState;

            if(getState() != nullptr)
                getState()->_onLoad();
        }
    }

}