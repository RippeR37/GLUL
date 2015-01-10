#include <Utils/GL+/GUI/Window.h>

namespace GL {

    namespace GUI {

        Window::Window() : Util::Window() {

        }

        Window::~Window() {

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

    }

}