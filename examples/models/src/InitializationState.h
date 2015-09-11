#ifndef INITIALIZATIONSTATE_H_INCLUDED
#define INITIALIZATIONSTATE_H_INCLUDED

#include "WorkState.h"

#include <GLUL/Interfaces/State.h>

#include <memory>

class InitializationState : public GLUL::Interface::State {
    public:
        InitializationState(FW::Application* application);
        ~InitializationState();

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

    private:
        FW::Application* _application;
        std::unique_ptr<GLUL::Interface::State> _workState;
};

#endif