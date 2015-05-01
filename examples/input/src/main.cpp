#include <Utils/Logger.h>
#include <Utils/Window.h>
#include <Utils/Input/EventHandler.h>

#include <iostream>
#include <string>

/**
 * Custom input handler class.
 * This interface can be implemented by any class.
 *
 * It has to implement methods:
 *   - void handleInputEvent(const Util::InputEvent&) const
 */

class MyInputHandler : public Util::Input::EventHandler {
    public:
        void handleInputEvent(const Util::Input::Event& inputEvent) const {
            switch(inputEvent.getType()) {
                case Util::Input::Event::Type::Key: 
                    handleKeyInputEvent(*inputEvent.asKeyEvent()); 
                    break;

                case Util::Input::Event::Type::MouseButton:
                    handleMouseButtonInputEvent(*inputEvent.asMouseButtonEvent());
                    break;
            }
        }

        void handleKeyInputEvent(const Util::Input::KeyEvent& keyEvent) const {
            std::string action;

            switch(keyEvent.getAction()) {
                case Util::Input::Action::Press:    action = "pressed "; break;
                case Util::Input::Action::Repeat:   action = "repetead"; break;
                case Util::Input::Action::Release:  action = "released"; break;
            }

            std::cout << "Key " << action << " [id 'sign']: " 
                      << "'" << static_cast<unsigned char>(keyEvent.getKey()) << "' - " 
                      << static_cast<unsigned int>(keyEvent.getKey()) << std::endl;
        }

        void handleMouseButtonInputEvent(const Util::Input::MouseButtonEvent& mouseButtonEvent) const {
            std::string button;
            std::string action;

            switch(mouseButtonEvent.getMouseButton()) {
                case Util::Input::MouseButton::Left: button = "Left"; break;
                case Util::Input::MouseButton::Right: button = "Right"; break;
                case Util::Input::MouseButton::Middle: button = "Middle"; break;
            }

            switch(mouseButtonEvent.getAction()) {
                case Util::Input::Action::Press: action = "pressed"; break;
                case Util::Input::Action::Repeat: action = "repetead"; break;
                case Util::Input::Action::Release: action = "released"; break;
            }

            std::cout << button << " mouse button " << action << std::endl;
        }
};

/**
 * Main loop
 */
void run() {
    Util::Window window(800, 600, "Title");
    MyInputHandler myHandler;
    unsigned int closeTriggerID; // Trigger's id is neccessery to unregister it without removing all triggers
    
    window.create(); // Window creation
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f)); // Setting window's background to dark grey
    
    window.registerEvents(Util::Input::Event::Type::Key); // binding event callbacks to register keyboard-related events
    window.registerEvents(Util::Input::Event::Type::MouseButton); // binding event callbacks to register mouse-button-related events

    window.eventAggregator.registerHandler(Util::Input::Event::Type::Key, &myHandler); // register handler for key input events 
    window.eventAggregator.registerHandler(Util::Input::Event::Type::MouseButton, &myHandler); // register handler for mouse button input events 
    
    // Trigger for closing window
    closeTriggerID = window.eventAggregator.registerTrigger( // note that if you plan to remove trigger in future, you have to obtain it's ID
        Util::Input::Event::Type::Key,
        [&](Util::Input::Event& inputEvent) {
            Util::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent(); // obtaining reference with KeyEvent type if you register handler/trigger 
                                                                        // for more then one Event::Type then you should check which type it is 
                                                                        // using Event::getType() method here we only register it for Event::Type::Key
                                                                        // events so we can skip it

            if(keyEvent.getKey() == Util::Input::Key::Escacpe)
                window.destroy();
        }
    );

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        // do some stuff

        window.update();
    }
}

/**
 * Start of application
 */
int main() {
    try {
        run();

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
