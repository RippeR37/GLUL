#include "ExampleState.h"

#include <Utils/Frameworks/Application.h>
#include <Utils/TimeLoop.h>
#include <Utils/AABB.h>

ExampleState::ExampleState(FW::Application& application) : Application(application) {

}

ExampleState::~ExampleState() {

}

void ExampleState::update(const double frameTime) {
    Util::TimeLoop::semiFixed(Application.Window.getFrameTime(), 1.0f / 120.0f, [](double deltaTime) {
        // update here
    });
}

void ExampleState::render() {
    GL::Context::Current.clearBuffers(GL::Context::BufferMask::Color);

    // render here
}

void ExampleState::onLoad() {
    // Window 
    Application.Window.setSize(800u, 600u);
    Application.Window.setTitle("Title");
    Application.Window.create();
    Application.Window.setDestroyCallback([&]() {
        Application.signalExit();
    });

    // OpenGL context reference binding (for ease of use)
    GL::Context::Current = Application.Window.getContext();
    GL::Context::Current.setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
}

void ExampleState::onUnload() {
    GL::Context::Current = GL::Context::DefaultContext;
    Application.Window.destroy();

    // cleanup
}

void ExampleState::signalExit() {
    changeTo(nullptr);
}