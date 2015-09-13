#include <GLUL/Logger.h>
#include <GLUL/Window.h>
#include <GLUL/Input/EventHandler.h>
#include <GLUL/Input/EventTrigger.h>

#include <iostream>
#include <string>

/**
 * Custom input handler class.
 * This interface can be implemented by any class.
 *
 * It has to implement methods:
 *   - void handleInputEvent(const GLUL::InputEvent&) const
 */

class MyInputHandler : public GLUL::Input::EventHandler {
    public:
        /**
         * Handler decides which type of input event it was and redirects it to proper method.
         */
        void handleInputEvent(const GLUL::Input::Event& inputEvent) {
            switch(inputEvent.getType()) {
                case GLUL::Input::Event::Type::Character:
                    handleCharacterInputEvent(*inputEvent.asCharacterEvent()); break;

                case GLUL::Input::Event::Type::Key: 
                    handleKeyInputEvent(*inputEvent.asKeyEvent()); break;

                case GLUL::Input::Event::Type::MouseButton:
                    handleMouseButtonInputEvent(*inputEvent.asMouseButtonEvent()); break;

                case GLUL::Input::Event::Type::MouseMovement:
                    handleMouseMovementInputEvent(*inputEvent.asMouseMovementEvent()); break;

                case GLUL::Input::Event::Type::MouseScroll:
                    handleMouseScrollInputEvent(*inputEvent.asMouseScrollEvent()); break;
            }
        }

        /**
         * Handler for character input events (ASCII text)
         */
        void handleCharacterInputEvent(const GLUL::Input::CharacterEvent& characterEvent) {
            std::cout << "Character entered: " << characterEvent.getCharacter() << "] - ASCII: ";

            if(characterEvent.isASCII()) {
                std::cout << "true (" << characterEvent.asASCII() << ")";
            } else {
                std::cout << "false";
            }

            std::cout << std::endl;
        }

        /**
         * Handler for keyboard-related events
         */
        void handleKeyInputEvent(const GLUL::Input::KeyEvent& keyEvent) {
            std::string action;

            switch(keyEvent.getAction()) {
                case GLUL::Input::Action::Press:    action = "pressed "; break;
                case GLUL::Input::Action::Repeat:   action = "repetead"; break;
                case GLUL::Input::Action::Release:  action = "released"; break;
            }

            std::cout << "Key " << action << " [id 'sign']: " 
                      << "'" << static_cast<unsigned char>(keyEvent.getKey()) << "' - " 
                      << static_cast<unsigned int>(keyEvent.getKey()) << std::endl;
        }
        
        /**
         * Handler for mouse-button-related events
         */
        void handleMouseButtonInputEvent(const GLUL::Input::MouseButtonEvent& mouseButtonEvent) {
            std::string button;
            std::string action;

            switch(mouseButtonEvent.getMouseButton()) {
                case GLUL::Input::MouseButton::Left: button = "Left"; break;
                case GLUL::Input::MouseButton::Right: button = "Right"; break;
                case GLUL::Input::MouseButton::Middle: button = "Middle"; break;
            }

            switch(mouseButtonEvent.getAction()) {
                case GLUL::Input::Action::Press: action = "pressed"; break;
                case GLUL::Input::Action::Repeat: action = "repetead"; break;
                case GLUL::Input::Action::Release: action = "released"; break;
            }

            std::cout << button << " mouse button " << action << std::endl;
        }
        
        /**
         * Handler for mouse-movement-related events
         */
        void handleMouseMovementInputEvent(const GLUL::Input::MouseMovementEvent& mouseMovementEvent) {
            std::cout << "Mouse cursor now points: " << mouseMovementEvent.getX() << "x" << mouseMovementEvent.getY() << std::endl;
        }
        
        /**
         * Handler for mouse-scroll-related events
         */
        void handleMouseScrollInputEvent(const GLUL::Input::MouseScrollEvent& mouseScrollEvent) {
            std::string direction = (mouseScrollEvent.getDirection() == GLUL::Input::ScrollDirection::Up ? "up" : "down");

            std::cout << "Mouse scroll direction: " << direction << std::endl;
        }
};

/**
 * Set window to register events with types: Key, MouseButton, MouseMovement, MouseScroll
 */
void setupInputEvents(GLUL::Window& window) {
    window.registerEvents(); // enables registering all events, without need to specify them yourself
    
    /*
    window.registerEvents({
        GLUL::Input::Event::Type::Character,
        GLUL::Input::Event::Type::Key,
        GLUL::Input::Event::Type::MouseButton,
        GLUL::Input::Event::Type::MouseMovement,
        GLUL::Input::Event::Type::MouseScroll
    });
    */
}

/**
 * Subscribe handler to recieve events with types: Key, MouseButton, MouseMovement, MouseScroll
 */
void registerHandler(GLUL::Window& window, GLUL::Input::EventHandler* handler) {
    window.eventAggregator.registerHandler(
        {
            GLUL::Input::Event::Type::Character,
            GLUL::Input::Event::Type::Key,
            GLUL::Input::Event::Type::MouseButton,
            GLUL::Input::Event::Type::MouseMovement,
            GLUL::Input::Event::Type::MouseScroll
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
unsigned int registerQuitTrigger(GLUL::Window& window) {
    unsigned int triggerID; // note that if you plan to remove trigger in future, you have to obtain it's ID
    
    triggerID = window.eventAggregator.registerTrigger(
        GLUL::Input::Event::Type::Key,
        [&](GLUL::Input::Event& inputEvent) {
            // Obtaining reference with KeyEvent type. If you register handler/trigger for more then one Event::Type then you should check
            // which type it is using Event::getType() method. Here we only register it for Event::Type::Key events so we can skip it
            GLUL::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent(); 

            if(keyEvent.getKey() == GLUL::Input::Key::Escacpe)
                window.destroy();
        }
    );

    return triggerID;
}

/**
 * Register automatic trigger (using GLUL::Input::EventTrigger class) for pressing 'Enter' key
 * This trigger will unregister itself upon destruction from binded EventAggregator
 *
 * WARNING: Trigger object has to be destryoed (or reseted) before destruction of Window! Otherwise, it's destructor will cause crash!
 */
void registerEnterTrigger(GLUL::Input::EventTrigger& trigger) {
    trigger.setFunction(
        GLUL::Input::Event::Type::Key,
        [](GLUL::Input::Event& event) {
            GLUL::Input::KeyEvent& keyEvent = *event.asKeyEvent();

            if(keyEvent.getAction() == GLUL::Input::Action::Press) {
                if(keyEvent.getKey() == GLUL::Input::Key::Enter) {
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
    GLUL::Window window(800, 600, "Title");
    MyInputHandler myHandler;

    // Trigger binded to window's EventAggregator. It will automatically unregister when destroyed.
    // WARNING: This object has to be destroyed or reseted before it's bounded EventAggregator! Otherwise it will crash!
    GLUL::Input::EventTrigger myTrigger(window.eventAggregator);

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
