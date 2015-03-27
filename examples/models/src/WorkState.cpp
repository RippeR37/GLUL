#include "WorkState.h"

#include <Utils/Logger.h>
#include <Utils/Interfaces/Model.h>
#include <Utils/Frameworks/Application.h>
#include <Utils/TimeLoop.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

WorkState::WorkState(Util::Interface::State* parentState, FW::Application* application) {
    _parentState = parentState;
    _application = application;
}

WorkState::~WorkState() {

}

void WorkState::update(const double frameTime) {
    Util::TimeLoop::semiFixed(frameTime, 1.0f / 120.0f, [](double deltaTime) {
        (void) deltaTime;

        // update objects here
    });

    if(glfwGetKey(_application->Window, GLFW_KEY_ESCAPE))
        changeTo(_parentState);
}

void WorkState::render() {
    GL::Context::Current.clearBuffers(GL::Context::BufferMask::Color_Depth);

    _modelOBJ[0].render(_pipeline);
    _modelOBJ[1].render(_pipeline);
}

void WorkState::onLoad() {
    GL::Context::Current.setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    // Set OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    // Load models
    bool loaded[2];
    loaded[0] = _modelOBJ[0].load("assets/models/teapot/teapot.obj");
    loaded[1] = _modelOBJ[1].load("assets/models/suzanne/suzanne.obj");

    _modelOBJ[0].setMatrix(glm::translate(glm::mat4(1.0), glm::vec3(-1.5, -0.5, -4.0)));
    _modelOBJ[1].setMatrix(glm::translate(glm::mat4(1.0), glm::vec3( 1.3,  0.0, -4.0)));

    if(!loaded[0] || !loaded[1]) {
        Util::Log::Stream("Example", "logExample.log");

        for(int i : { 0, 1 })
            if(!loaded[i])
                Util::Log::Stream("Example") << "OBJ model '" + _modelOBJ[0].getPath() + "' not loaded!";
    }
}

void WorkState::onUnload() {

}

void WorkState::signalExit() {
    changeTo(nullptr);
}