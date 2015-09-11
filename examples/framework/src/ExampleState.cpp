#include "ExampleState.h"

#include <GLUL/Frameworks/Application.h>
#include <GLUL/TimeLoop.h>

ExampleState::ExampleState(FW::Application& application) : Application(application) {

}

ExampleState::~ExampleState() {

}

void ExampleState::update(const double frameTime) {
    GLUL::TimeLoop::semiFixed(frameTime, 1.0f / 120.0f, [](double deltaTime) {
        (void) deltaTime;

        // update here
    });
}

void ExampleState::render() {
    GL::Context::Current->clearBuffers(GL::Context::BufferMask::Color);

    // render here
}

void ExampleState::onLoad() {
    // Window 
    Application.Window.setSize(800u, 600u);
    Application.Window.setTitle("Title");
    Application.Window.create();
    Application.Window.registerEvents();
    Application.Window.setDestroyCallback([&]() {
        Application.signalExit();
    });

    // OpenGL context settings
    GL::Context::Current->setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    // Registering state as event handler
    GLUL::Windows::Get("FW::Application::Window::1")->eventAggregator.registerHandler(GLUL::Input::Event::Type::Key, this);
}

void ExampleState::onUnload() {
    // cleanup

    // Unregistering state as event handler
    GLUL::Windows::Get("FW::Application::Window::1")->eventAggregator.unregisterHandler(GLUL::Input::Event::Type::Key, this);
}

void ExampleState::signalExit() {
    changeTo(nullptr);
}

void ExampleState::handleInputEvent(const GLUL::Input::Event& inputEvent) {
    if(inputEvent.getType() == GLUL::Input::Event::Type::Key) {
        const GLUL::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent();

        if(keyEvent.getAction() == GLUL::Input::Action::Press) {
            switch(keyEvent.getKey()) {
                case GLUL::Input::Key::Escacpe:
                    signalExit();
                    break;

                default:
                    break;
            }
        }
    }
}