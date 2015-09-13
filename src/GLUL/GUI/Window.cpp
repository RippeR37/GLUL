#include <GLUL/GUI/Window.h>


namespace GLUL {

    namespace GUI {

        Window::Window() : GLUL::Window(), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    GLUL::Input::Event::Type::Character,
                    GLUL::Input::Event::Type::Key,
                    GLUL::Input::Event::Type::MouseButton, 
                    GLUL::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(unsigned int width, unsigned int height, const std::string& title) : GLUL::Window(width, height, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    GLUL::Input::Event::Type::Character,
                    GLUL::Input::Event::Type::Key,
                    GLUL::Input::Event::Type::MouseButton, 
                    GLUL::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(const glm::uvec2& size, const std::string& title) : GLUL::Window(size, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    GLUL::Input::Event::Type::Character,
                    GLUL::Input::Event::Type::Key,
                    GLUL::Input::Event::Type::MouseButton, 
                    GLUL::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::~Window() {
            this->eventAggregator.unregisterHandler(
                {
                    GLUL::Input::Event::Type::Character,
                    GLUL::Input::Event::Type::Key,
                    GLUL::Input::Event::Type::MouseButton, 
                    GLUL::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        void Window::update() {
            GLUL::Window::update();

            Container::update(getFrameTime());
        }
        
        void Window::setSize(unsigned int width, unsigned int height) {
            GLUL::Window::setSize(width, height);
        }

        void Window::setSize(const glm::vec2& size) {
            GLUL::Window::setSize(glm::uvec2(size));
        }

        void Window::setSize(const glm::uvec2& size) {
            GLUL::Window::setSize(size);
        }
        
        void Window::handleInputEvent(const GLUL::Input::Event& inputEvent) {
            switch(inputEvent.getType()) {
                case GLUL::Input::Event::Type::Character:
                    {
                        const GLUL::Input::CharacterEvent& thisEvent = *(inputEvent.asCharacterEvent());

                        if(thisEvent.isASCII()) {
                            unsigned char character;
                            std::string text;

                            character = thisEvent.asASCII();
                            text = reinterpret_cast<char&>(character);

                            onTextInput(*this, Event::TextInput(text));
                        }
                    }
                    break;

                case GLUL::Input::Event::Type::Key:
                    {
                        const GLUL::Input::KeyEvent& thisEvent = *(inputEvent.asKeyEvent());

                        if(thisEvent.getAction() == GLUL::Input::Action::Press) {
                            onKeyStroke(*this, Event::KeyStroke(thisEvent.getKey()));
                        }
                    }
                    break;

                case GLUL::Input::Event::Type::MouseButton:
                    {
                        const GLUL::Input::MouseButtonEvent& thisEvent = *(inputEvent.asMouseButtonEvent());

                        if(thisEvent.getAction() == GLUL::Input::Action::Press) {
                            onMouseClick(*this, Event::MouseClick(thisEvent.getMouseButton(), thisEvent.getPosition()));
                        } else if(thisEvent.getAction() == GLUL::Input::Action::Release) {
                            onMouseRelease(*this, Event::MouseRelease(thisEvent.getMouseButton(), thisEvent.getPosition()));
                        }
                    }
                    break;

                case GLUL::Input::Event::Type::MouseMovement:
                    {
                        const GLUL::Input::MouseMovementEvent& thisEvent = *(inputEvent.asMouseMovementEvent());

                        onMouseMove(*this, Event::MouseMove(thisEvent.getPosition()));
                    }
                    break;

                default: break;
            }
        }
    }

}
