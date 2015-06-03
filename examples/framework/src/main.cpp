#include "ExampleState.h"

#include <Utils/Logger.h>
#include <Utils/Exception.h>
#include <Utils/Frameworks/Application.h>

int main(int argc, char* argv[]) {
    try {
        FW::Application application;
        ExampleState initialState(application);

        application.setArguments(argc, argv);
        application.run(&initialState);

    } catch(const Util::Exception::FatalError& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        Util::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}