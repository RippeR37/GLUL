#include "ExampleState.h"

#include <Utils/Frameworks/Application.h>
#include <Utils/TimeLoop.h>

ExampleState::ExampleState(FW::Application& application) : Application(application) {

}

ExampleState::~ExampleState() {

}

void ExampleState::update(const double frameTime) {
    Util::TimeLoop::semiFixed(frameTime, 1.0f / 120.0f, [](double deltaTime) {
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
    Util::Windows::Get("FW::Application::Window::1")->eventAggregator.registerHandler(Util::Input::Event::Type::Key, this);
}

void ExampleState::onUnload() {
    // cleanup

    // Unregistering state as event handler
    Util::Windows::Get("FW::Application::Window::1")->eventAggregator.unregisterHandler(Util::Input::Event::Type::Key, this);
}

void ExampleState::signalExit() {
    changeTo(nullptr);
}

void ExampleState::handleInputEvent(const Util::Input::Event& inputEvent) {
    if(inputEvent.getType() == Util::Input::Event::Type::Key) {
        const Util::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent();

        if(keyEvent.getAction() == Util::Input::Action::Press) {
            switch(keyEvent.getKey()) {
                case Util::Input::Key::Escacpe:
                    signalExit();
                    break;

                default:
                    break;
            }
        }
    }
}