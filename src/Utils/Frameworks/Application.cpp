#include <Utils/Frameworks/Application.h>

namespace FW {

    Util::Window& Application::Window = Application::getInstance().getWindow();


    Application::Application() {
        setArguments(0, nullptr);
    }

    Application::~Application() {

    }

    Application& Application::getInstance() {
        static Application instance;
        return instance;
    }

    Util::Window& Application::getWindow() {
        return _window;
    }

    void Application::run(Util::Interface::State* initialState) {
        getInstance().setState(initialState);

        while(getInstance().getState() != Util::Interface::State::Quit) {
            getInstance().getWindow().update();

            getInstance().getState()->handleInput();
            getInstance().getState()->_update(getInstance().getWindow().getFrameTime());
            getInstance().getState()->_render();

            getInstance().setState(getInstance().getState()->getNext());
        }
    }

    void Application::signalExit() {
        if(getInstance().getState())
            getInstance().getState()->signalExit();
    }

    const std::string& Application::getArgument(int id) throw(std::out_of_range) {
        return getInstance()._arguments.at(id);
    }

    const std::vector<std::string>& Application::getArguments() {
        return getInstance()._arguments;
    }

    void Application::setArguments(int argumentCount, char* arguments[]) {
        getInstance()._arguments.resize(argumentCount);

        for(int i = 0; i < argumentCount; ++i)
            getInstance()._arguments[i] = std::string(arguments[i]);
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