#ifndef WORKSTATE_H_INCLUDED
#define WORKSTATE_H_INCLUDED

#include <Utils/Interfaces/State.h>
#include <Utils/GL+/Models/OBJ.h>

#include <memory>

class WorkState : public Util::Interface::State {
    public:
        WorkState(Util::Interface::State* parentState, FW::Application* application);
        ~WorkState();

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

    private:
        FW::Application* _application;
        Util::Interface::State* _parentState;

        GL::Pipeline _pipeline;
        GL::Model::OBJ _modelOBJ[2];

};

#endif