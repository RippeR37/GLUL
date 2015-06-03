#ifndef UTILS_FRAMEWORKS_APPLICATION_H_INCLUDED
#define UTILS_FRAMEWORKS_APPLICATION_H_INCLUDED

#include <Utils/Window.h>
#include <Utils/Interfaces/State.h>

#include <vector>

namespace FW {

    class Application {
        public:
            Application();
            ~Application();

            void run(Util::Interface::State* initialState);
            void signalExit();

            const std::string& getArgument(int id) throw(std::out_of_range);
            const std::vector<std::string>& getArguments();

            void setArguments(int argumentsCount, char* arguments[]);

            Util::Window& Window;

        private:
            Util::Window& getWindow();
            Util::Interface::State* getState();
            void setState(Util::Interface::State* const newState);

            Util::Window _window;
            Util::Interface::State* _state;
            std::vector<std::string> _arguments;
    };

}

#endif