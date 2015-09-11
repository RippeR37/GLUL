#ifndef WORKSTATE_H_INCLUDED
#define WORKSTATE_H_INCLUDED

#include <GLUL/GL++/Models/OBJ.h>
#include <GLUL/Interfaces/State.h>

#include <memory>

class WorkState : public GLUL::Interface::State {
    public:
        WorkState(GLUL::Interface::State* parentState);
        ~WorkState();

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

        void handleInputEvent(const GLUL::Input::Event& inputEvent);

    private:
        GLUL::Interface::State* _parentState;

        GL::Pipeline _pipeline;
        GL::Model::OBJ _modelOBJ[2];

};

#endif