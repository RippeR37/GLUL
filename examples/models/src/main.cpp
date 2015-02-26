#include "InitializationState.h"

#include <Utils/Exception.h>
#include <Utils/Frameworks/Application.h>

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    try {
        FW::Application application;
        InitializationState initialState(&application);

        application.setArguments(argc, argv);
        application.run(&initialState);

    } catch(const Util::Exception::FatalError& exception) {
        std::cerr << "Fatal error occured:" << std::endl;
        std::cerr << exception.what() << std::endl;
        system("pause");

    } catch(const std::exception& exception) {
        std::cerr << "Exception thrown:" << std::endl;
        std::cerr << exception.what() << std::endl;
        system("pause");

    } catch(...) {
        std::cerr << "Unidentified exception unhandled" << std::endl;
        system("pause");
    }

    return 0;
}