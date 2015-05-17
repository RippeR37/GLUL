#include <Utils/Logger.h>
#include <Utils/Window.h>
#include <Utils/Input/EventHandler.h>
#include <Utils/Input/EventTrigger.h>

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
        /**
         * Handler decides which type of input event it was and redirects it to proper method.
         */
        void handleInputEvent(const Util::Input::Event& inputEvent) {
            switch(inputEvent.getType()) {
                case Util::Input::Event::Type::Key: 
                    handleKeyInputEvent(*inputEvent.asKeyEvent()); break;

                case Util::Input::Event::Type::MouseButton:
                    handleMouseButtonInputEvent(*inputEvent.asMouseButtonEvent()); break;

                case Util::Input::Event::Type::MouseMovement:
                    handleMouseMovementInputEvent(*inputEvent.asMouseMovementEvent()); break;

                case Util::Input::Event::Type::MouseScroll:
                    handleMouseScrollInputEvent(*inputEvent.asMouseScrollEvent()); break;
            }
        }

        /**
         * Handler for keyboard-related events
         */
        void handleKeyInputEvent(const Util::Input::KeyEvent& keyEvent) {
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
        
        /**
         * Handler for mouse-button-related events
         */
        void handleMouseButtonInputEvent(const Util::Input::MouseButtonEvent& mouseButtonEvent) {
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
        
        /**
         * Handler for mouse-movement-related events
         */
        void handleMouseMovementInputEvent(const Util::Input::MouseMovementEvent& mouseMovementEvent) {
            std::cout << "Mouse cursor now points: " << mouseMovementEvent.getX() << "x" << mouseMovementEvent.getY() << std::endl;
        }
        
        /**
         * Handler for mouse-scroll-related events
         */
        void handleMouseScrollInputEvent(const Util::Input::MouseScrollEvent& mouseScrollEvent) {
            std::string direction = (mouseScrollEvent.getDirection() == Util::Input::ScrollDirection::Up ? "up" : "down");

            std::cout << "Mouse scroll direction: " << direction << std::endl;
        }
};

/**
 * Set window to register events with types: Key, MouseButton, MouseMovement, MouseScroll
 */
void setupInputEvents(Util::Window& window) {
    window.registerEvents(); // enables registering all events, without need to specify them yourself
    
    /*
    window.registerEvents({
        Util::Input::Event::Type::Key,
        Util::Input::Event::Type::MouseButton,
        Util::Input::Event::Type::MouseMovement,
        Util::Input::Event::Type::MouseScroll
    });
    */
}

/**
 * Subscribe handler to recieve events with types: Key, MouseButton, MouseMovement, MouseScroll
 */
void registerHandler(Util::Window& window, Util::Input::EventHandler* handler) {
    window.eventAggregator.registerHandler(
        {
            Util::Input::Event::Type::Key,
            Util::Input::Event::Type::MouseButton,
            Util::Input::Event::Type::MouseMovement,
            Util::Input::Event::Type::MouseScroll
        },
        handler
    );
}

/**
 * Register manual trigger for closing window using 'Escape' key
 * 
 * WARNING: This trigger will stay active until:
 * - you invoke clear() or clearTriggers() on EventAggregator object (in this case window.EventAggregator)
 * - eventAggregator gets destroyed
 * To remove it manually, save trigger's ID and when time comes, use removeTrigger(_type(s)_, triggerID) method on EventAggregator
 */
unsigned int registerQuitTrigger(Util::Window& window) {
    unsigned int triggerID; // note that if you plan to remove trigger in future, you have to obtain it's ID
    
    triggerID = window.eventAggregator.registerTrigger(
        Util::Input::Event::Type::Key,
        [&](Util::Input::Event& inputEvent) {
            // Obtaining reference with KeyEvent type. If you register handler/trigger for more then one Event::Type then you should check
            // which type it is using Event::getType() method. Here we only register it for Event::Type::Key events so we can skip it
            Util::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent(); 

            if(keyEvent.getKey() == Util::Input::Key::Escacpe)
                window.destroy();
        }
    );

    return triggerID;
}

/**
 * Register automatic trigger (using Util::Input::EventTrigger class) for pressing 'Enter' key
 * This trigger will unregister itself upon destruction from binded EventAggregator
 *
 * WARNING: Trigger object has to be destryoed (or reseted) before destruction of Window! Otherwise, it's destructor will cause crash!
 */
void registerEnterTrigger(Util::Input::EventTrigger& trigger) {
    trigger.setFunction(
        Util::Input::Event::Type::Key,
        [](Util::Input::Event& event) {
            Util::Input::KeyEvent& keyEvent = *event.asKeyEvent();

            if(keyEvent.getAction() == Util::Input::Action::Press) {
                if(keyEvent.getKey() == Util::Input::Key::Enter) {
                    std::cout << "MyTrigger: Enter key was pressed!" << std::endl;
                }
            }
        }
    );
}

/**
 * Main loop
 */
void run() {
    Util::Window window(800, 600, "Title");
    MyInputHandler myHandler;

    // Trigger binded to window's EventAggregator. It will automatically unregister when destroyed.
    // WARNING: This object has to be destroyed or reseted before it's bounded EventAggregator! Otherwise it will crash!
    Util::Input::EventTrigger myTrigger(window.eventAggregator);

    window.create();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));
    
    setupInputEvents(window);               // set window to listen for events
    registerHandler(window, &myHandler);    // set myHandler as one of the recievers of events notifications
    registerQuitTrigger(window);            // set manualy input trigger (for esc key) to close window
    registerEnterTrigger(myTrigger);        // set automaitcally myTrigger's function to write text upon pressing Enter key

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);
        window.update();

        // do some stuff
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
