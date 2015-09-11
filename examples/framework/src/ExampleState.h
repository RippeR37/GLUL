#ifndef EXAMPLESTATE_H_INCLUDED
#define EXAMPLESTATE_H_INCLUDED

#include <GLUL/Interfaces/State.h>

class ExampleState : public GLUL::Interface::State {
    public:
        ExampleState(FW::Application& application);
        ~ExampleState();

        ExampleState& operator=(const ExampleState&) = delete;

        void update(const double frameTime);
        void render();
        void onLoad();
        void onUnload();
        void signalExit();

        void handleInputEvent(const GLUL::Input::Event& inputEvent);

    private:
        FW::Application& Application;
};

#endif