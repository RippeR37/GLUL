#include <Utils/GL+/GUI/Window.h>

namespace GL {

    namespace GUI {

        Window::Window() : Util::Window(), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(unsigned int width, unsigned int height, const std::string& title) : Util::Window(width, height, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::Window(const glm::uvec2& size, const std::string& title) : Util::Window(size, title), Container(nullptr) {
            this->eventAggregator.registerHandler(
                {
                    Util::Input::Event::Type::MouseButton, 
                    Util::Input::Event::Type::MouseMovement
                },
                this
            );
        }

        Window::~Window() {
            this->eventAggregator.unregisterHandler(
                {
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
                case Util::Input::Event::Type::MouseButton:
                    {
                        const Util::Input::MouseButtonEvent& thisEvent = *(inputEvent.asMouseButtonEvent());

                        if(thisEvent.getAction() == Util::Input::Action::Press)
                            onClick(*this, Event::OnClick(thisEvent.getMouseButton(), thisEvent.getPosition()));
                    }
                    break;

                default: break;
            }
        }
    }

}