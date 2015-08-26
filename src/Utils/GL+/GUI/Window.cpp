#include <Utils/GL+/GUI/Window.h>


namespace GL {

    namespace GUI {

        Window::Window() : Util::Window(), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::Key,
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(unsigned int width, unsigned int height, const std::string& title) : Util::Window(width, height, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::Key,
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(const glm::uvec2& size, const std::string& title) : Util::Window(size, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::Key,
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::~Window() {
            this->eventAggregator.unregisterHandler(
                {
                    Util::Input::Event::Type::Key,
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        void Window::update() {
            Util::Window::update();

            Container::update(getFrameTime());
        }
        
        void Window::setSize(unsigned int width, unsigned int height) {
            Util::Window::setSize(width, height);
        }

        void Window::setSize(const glm::vec2& size) {
            Util::Window::setSize(glm::uvec2(size));
        }

        void Window::setSize(const glm::uvec2& size) {
            Util::Window::setSize(size);
        }
        
        void Window::handleInputEvent(const Util::Input::Event& inputEvent) {
            switch(inputEvent.getType()) {
                case Util::Input::Event::Type::Key:
                    {
                        const Util::Input::KeyEvent& thisEvent = *(inputEvent.asKeyEvent());

                        if(thisEvent.getAction() == Util::Input::Action::Press) {
                            onKeyStroke(*this, Event::KeyStroke(thisEvent.getKey()));
                        }
                    }
                    break;

                case Util::Input::Event::Type::MouseButton:
                    {
                        const Util::Input::MouseButtonEvent& thisEvent = *(inputEvent.asMouseButtonEvent());

                        if(thisEvent.getAction() == Util::Input::Action::Press) {
                            onMouseClick(*this, Event::MouseClick(thisEvent.getMouseButton(), thisEvent.getPosition()));
                        } else if(thisEvent.getAction() == Util::Input::Action::Release) {
                            onMouseRelease(*this, Event::MouseRelease(thisEvent.getMouseButton(), thisEvent.getPosition()));
                        }
                    }
                    break;

                case Util::Input::Event::Type::MouseMovement:
                    {
                        const Util::Input::MouseMovementEvent& thisEvent = *(inputEvent.asMouseMovementEvent());

                        onMouseMove(*this, Event::MouseMove(thisEvent.getPosition()));
                    }
                    break;

                default: break;
            }
        }
    }

}
