#include "ExampleState.h"

#include <GLUL/Logger.h>
#include <GLUL/Exception.h>
#include <GLUL/Frameworks/Application.h>

int main(int argc, char* argv[]) {
    try {
        FW::Application application;
        ExampleState initialState(application);

        application.setArguments(argc, argv);
        application.run(&initialState);

    } catch(const GLUL::Exception::FatalError& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}