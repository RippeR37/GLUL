#ifndef EXAMPLESTATE_H_INCLUDED
#define EXAMPLESTATE_H_INCLUDED

#include <Utils/Interfaces/State.h>

class ExampleState : public Util::Interface::State {
    public:
        ExampleState(FW::Application& application);
        ~ExampleState();

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

        void handleInputEvent(const Util::Input::Event& inputEvent);

    private:
        FW::Application& Application;
};

#endif