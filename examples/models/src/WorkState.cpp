#include "WorkState.h"

#include <GLUL/Logger.h>
#include <GLUL/Interfaces/Model.h>
#include <GLUL/Frameworks/Application.h>
#include <GLUL/TimeLoop.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

WorkState::WorkState(GLUL::Interface::State* parentState) {
    _parentState = parentState;
}

WorkState::~WorkState() {

}

void WorkState::update(const double frameTime) {
    GLUL::TimeLoop::semiFixed(frameTime, 1.0f / 120.0f, [](double deltaTime) {
        (void) deltaTime;

        // update objects here
    });
}

void WorkState::render() {
    GL::Context::Current->clearBuffers(GL::Context::BufferMask::Color_Depth);

    _modelOBJ[0].render(_pipeline);
    _modelOBJ[1].render(_pipeline);
}

void WorkState::onLoad() {
    GL::Context::Current->setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    GLUL::Windows::Get("FW::Application::Window::1")->eventAggregator.registerHandler(GLUL::Input::Event::Type::Key, this);

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
        GLUL::Log::Stream("Example", "logExample.log");

        for(int i : { 0, 1 })
            if(!loaded[i])
                GLUL::Log::Stream("Example") << "OBJ model '" + _modelOBJ[0].getPath() + "' not loaded!";
    }
}

void WorkState::onUnload() {
    GLUL::Windows::Get("FW::Application::Window::1")->eventAggregator.unregisterHandler(GLUL::Input::Event::Type::Key, this);
}

void WorkState::signalExit() {
    changeTo(nullptr);
}

void WorkState::handleInputEvent(const GLUL::Input::Event& inputEvent) {
    if(inputEvent.getType() == GLUL::Input::Event::Type::Key) {
        const GLUL::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent();

        if(keyEvent.getAction() == GLUL::Input::Action::Press) {
            switch(keyEvent.getKey()) {
                case GLUL::Input::Key::Escacpe: 
                    const_cast<WorkState*>(this)->changeTo(_parentState);
                    break;

                default:
                    break;
            }
        }
    }
}