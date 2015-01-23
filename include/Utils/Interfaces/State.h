#ifndef UTILS_INTERFACES_STATE_H_INCLUDED
#define UTILS_INTERFACES_STATE_H_INCLUDED

namespace Util {
    
    namespace Interface {

        class State {
            public:
                State();
                virtual ~State();

                virtual void update(const double frameTime) = 0;
                virtual void render() = 0;
                virtual void onLoad() = 0;
                virtual void onUnload() = 0;
                virtual void signalExit() = 0;

                virtual void handleInput();
                State* getNext();

                static const State* const Quit;

            protected:
                void changeTo(State* nextState);
                bool shouldSkip();

                State* _next;
        };

    }

}

#endif