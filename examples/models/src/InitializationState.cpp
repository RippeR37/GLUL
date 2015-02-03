#include "InitializationState.h"

#include <Utils/Frameworks/Application.h>
#include <Utils/TimeLoop.h>

#include <iostream>

InitializationState::InitializationState() {

}

InitializationState::~InitializationState() {

}

void InitializationState::update(const double frameTime) {
    if(_workState)
        _workState->update(frameTime);
    else
        std::cout << "InitializationState::update()" << std::endl;
}

void InitializationState::render() {
    if(_workState)
        _workState->render();
}

void InitializationState::onLoad() {
    if(!_workState) {
        // Window initialization
        FW::Application::Window.setSize(800u, 600u);
        FW::Application::Window.setTitle("Title");
        FW::Application::Window.create();
        FW::Application::Window.setDestroyCallback([]() {
            FW::Application::signalExit();
        });

        // OpenGL context reference binding (for ease of use)
        GL::Context::Current = FW::Application::Window.getContext();
        GL::Context::Current.setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        // Change to application's main state
        _workState.reset(new WorkState(this));
        changeTo(_workState.get());

    } else {
        _workState.reset(nullptr);
        changeTo(nullptr); //otherwise - quit
    }
}

void InitializationState::onUnload() {
    if(!_workState) {
        GL::Context::Current = GL::Context::DefaultContext;
        FW::Application::Window.destroy();
    }
}

void InitializationState::signalExit() {
    changeTo(nullptr);
}