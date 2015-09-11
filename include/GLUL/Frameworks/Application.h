#pragma once

#include <GLUL/Window.h>
#include <GLUL/Interfaces/State.h>

#include <vector>


namespace FW {

    class GLUL_API Application {
        public:
            Application();
            ~Application();

            void run(GLUL::Interface::State* initialState);
            void signalExit();

            const std::string& getArgument(int id) throw(std::out_of_range);
            const std::vector<std::string>& getArguments();

            void setArguments(int argumentsCount, char* arguments[]);

            GLUL::Window& Window;

        private:
            GLUL::Window& getWindow();
            GLUL::Interface::State* getState();
            void setState(GLUL::Interface::State* const newState);

            GLUL::Window _window;
            GLUL::Interface::State* _state;
            std::vector<std::string> _arguments;
    };

}
