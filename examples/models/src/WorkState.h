#ifndef WORKSTATE_H_INCLUDED
#define WORKSTATE_H_INCLUDED

#include <Utils/GL+/Models/OBJ.h>
#include <Utils/Interfaces/State.h>

#include <memory>

class WorkState : public Util::Interface::State {
    public:
        WorkState(Util::Interface::State* parentState);
        ~WorkState();

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

        void handleInputEvent(const Util::Input::Event& inputEvent);

    private:
        Util::Interface::State* _parentState;

        GL::Pipeline _pipeline;
        GL::Model::OBJ _modelOBJ[2];

};

#endif