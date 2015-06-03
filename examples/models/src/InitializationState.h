#ifndef INITIALIZATIONSTATE_H_INCLUDED
#define INITIALIZATIONSTATE_H_INCLUDED

#include "WorkState.h"

#include <Utils/Interfaces/State.h>

#include <memory>

class InitializationState : public Util::Interface::State {
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
        std::unique_ptr<Util::Interface::State> _workState;
};

#endif