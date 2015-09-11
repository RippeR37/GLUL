#include "InitializationState.h"

#include <GLUL/Frameworks/Application.h>
#include <GLUL/TimeLoop.h>

InitializationState::InitializationState(FW::Application* application) {
    _application = application;
}

InitializationState::~InitializationState() {

}

void InitializationState::update(const double frameTime) {
    if(_workState)
        _workState->update(frameTime);
}

void InitializationState::render() {
    if(_workState)
        _workState->render();
}

void InitializationState::onLoad() {
    if(!_workState) {
        if(_application) {
            // Window initialization
            _application->Window.setSize(800u, 600u);
            _application->Window.setTitle("Title");
            _application->Window.create();
            _application->Window.registerEvents(GLUL::Input::Event::Type::Key);
            _application->Window.setDestroyCallback([&]() {
                _application->signalExit();
            });

            // Set window's background color
            GL::Context::Current->setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

            // Change to application's main state
            _workState.reset(new WorkState(this));
            changeTo(_workState.get());
        }

    } else {
        _workState.reset(nullptr);
        changeTo(nullptr); //otherwise - quit
    }
}

void InitializationState::onUnload() {
    if(!_workState) {
        _application->Window.destroy();
    }
}

void InitializationState::signalExit() {
    changeTo(nullptr);
}