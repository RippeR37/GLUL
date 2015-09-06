#ifndef UTILS_INTERFACES_STATE_H_INCLUDED
#define UTILS_INTERFACES_STATE_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Input/EventHandler.h>


namespace FW {
    class Application;
}

namespace Util {
    
    namespace Interface {

        class UTILS_API State : public Input::EventHandler {
            public:
                State();
                virtual ~State();

                virtual void update(const double frameTime) = 0;
                virtual void render() = 0;
                virtual void onLoad() = 0;
                virtual void onUnload() = 0;

                virtual void signalExit() = 0;
                virtual void handleInputEvent(const Input::Event& inputEvent);

                State* getNext();

                static const State* const Quit;

            protected:
                void changeTo(State* nextState);
                bool shouldSkip();

                State* _next;

            private:
                void _update(const double frameTime);
                void _render();
                void _onLoad();
                void _onUnload();

            public:
                friend class FW::Application;
        };

    }

}

#endif
