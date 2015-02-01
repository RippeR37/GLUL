#include "ExampleState.h"

#include <Utils/Frameworks/Application.h>
#include <Utils/TimeLoop.h>
#include <Utils/AABB.h>

#include <iostream>

ExampleState::ExampleState() {

}

ExampleState::~ExampleState() {

}

void ExampleState::update(const double frameTime) {
    Util::TimeLoop::semiFixed(FW::Application::Window.getFrameTime(), 1.0f / 120.0f, [](double deltaTime) {
        // update here
    });
}

void ExampleState::render() {
    // render here
}

void ExampleState::onLoad() {
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
}

void ExampleState::onUnload() {
    GL::Context::Current = GL::Context::DefaultContext;
    FW::Application::Window.destroy();

    // cleanup
}

void ExampleState::signalExit() {
    changeTo(nullptr);
}