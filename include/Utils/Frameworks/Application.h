#ifndef UTILS_FRAMEWORKS_APPLICATION_H_INCLUDED
#define UTILS_FRAMEWORKS_APPLICATION_H_INCLUDED

#include <Utils/Window.h>
#include <Utils/Interfaces/State.h>

#include <vector>

namespace FW {

    class Application {
        public:
            static void run(Util::Interface::State* initialState);
            static void signalExit();

            static const std::string& getArgument(int id) throw(std::out_of_range);
            static const std::vector<std::string>& getArguments();

            static void setArguments(int argumentsCount, char* arguments[]);

            static Util::Window& Window;

        private:
            static Application& getInstance();
            Util::Window& getWindow();

        private:
            Application();
            ~Application();

            Util::Interface::State* getState();
            void setState(Util::Interface::State* const newState);

            Util::Window _window;
            Util::Interface::State* _state;
            std::vector<std::string> _arguments;
    };

}

#endif